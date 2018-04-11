#define PTE_BITS_L1_SECTION             (0x2)  // 分页表类型为段页表
#define PAGE_TAB_L1_BASE_ADDR_MASK      (0xffffc000)  // 段页表基地址屏蔽位:前18位
#define PTE_L1_SECTION_PADDR_BASE_MASK  (0xfff00000)  // 物理基地址屏蔽位:前12位

#define VIRT_TO_PTE_L1_INDEX(addr)      (((addr)&0xfff00000)>>18) // 虚拟地址前14位, 12位地址,2位分页表类型
#define PTE_L1_SECTION_NO_CACHE_AND_WB  (0x0<<2)  // 默认禁用cache和write buffer
#define PTE_L1_SECTION_DOMAIN_DEFAULT   (0x0<<5)  // 域位
#define PTE_ALL_AP_L1_SECTION_DEFAULT   (0x1<<10) // AP位, 特权读写, 用户只读 

#define L1_PTR_BASE_ADDR                (0x30700000)  // 段页表基地址
#define PHYSICAL_MEM_ADDR               (0x30000000)  // 物理内存基地址
#define VIRTUAL_MEM_ADDR                (0x30000000)  // 虚拟内存基地址
#define MEM_MAP_SIZE                    (0x00800000)  // 8M大小物理内存映射
#define PHYSICAL_IO_ADDR                (0x48000000)  // 外设I/O物理基地址
#define VIRTUAL_IO_ADDR                 (0xc8000000)  // 外设I/O虚拟基地址
#define IO_MAP_SIZE                     (0x18000000)  // 外设I/O地址映射空间大小

#define PHYSICAL_VECTOR_ADDR            (0x30000000)  // 异常向量表物理基地址
#define VIRTUAL_VECTOR_ADDR             (0x00000000)  // 异常向量表虚拟基地址

unsigned int gen_l1_pte(unsigned int paddr)
{
	return (paddr&PTE_L1_SECTION_PADDR_BASE_MASK);
}

unsigned int gen_l1_pte_addr(unsigned int baddr, unsigned int vaddr)
{
	return ((baddr&PAGE_TAB_L1_BASE_ADDR_MASK) | VIRT_TO_PTE_L1_INDEX(vaddr));
}

/*
*  初始化MMU
*/
void init_sys_mmu(void)
{
	unsigned int pte;
	unsigned int pte_addr;
	int i;

    // 以1M为单位循环映射异常向量表到虚拟地址0x0处
	for(i=0; i<(MEM_MAP_SIZE>>20); ++i){
		pte = gen_l1_pte(PHYSICAL_VECTOR_ADDR+(i<<20));
		pte |= PTE_BITS_L1_SECTION;
		pte |= PTE_ALL_AP_L1_SECTION_DEFAULT;
		pte |= PTE_L1_SECTION_NO_CACHE_AND_WB;
		pte |= PTE_L1_SECTION_DOMAIN_DEFAULT;

		pte_addr = gen_l1_pte_addr(L1_PTR_BASE_ADDR, VIRTUAL_VECTOR_ADDR+(i<<20));  // 得到页表项地址
		*(volatile unsigned int *)pte_addr = pte;
	}

    // 以1M为单位循环映射物理内存地址
	for(i=0; i<(MEM_MAP_SIZE>>20); ++i){
		pte = gen_l1_pte(PHYSICAL_MEM_ADDR+(i<<20));
		pte |= PTE_BITS_L1_SECTION;
		pte |= PTE_ALL_AP_L1_SECTION_DEFAULT;
		pte |= PTE_L1_SECTION_NO_CACHE_AND_WB;
		pte |= PTE_L1_SECTION_DOMAIN_DEFAULT;

		pte_addr = gen_l1_pte_addr(L1_PTR_BASE_ADDR, VIRTUAL_MEM_ADDR+(i<<20));  // 得到页表项地址
		*(volatile unsigned int *)pte_addr = pte;
	}

    // 以1M为单位循环映射外部I/O地址
	for(i=0; i<(IO_MAP_SIZE>>20); ++i){
		pte = gen_l1_pte(PHYSICAL_IO_ADDR+(i<<20));
		pte |= PTE_BITS_L1_SECTION;
		pte |= PTE_ALL_AP_L1_SECTION_DEFAULT;
		pte |= PTE_L1_SECTION_NO_CACHE_AND_WB;
		pte |= PTE_L1_SECTION_DOMAIN_DEFAULT;
		pte_addr = gen_l1_pte_addr(L1_PTR_BASE_ADDR, VIRTUAL_IO_ADDR+(i<<20));  // 得到页表项地址
		*(volatile unsigned int *)pte_addr = pte;
	}

}

/*
*  使能MMU
*/
void start_mmu(void)
{
	unsigned int baddr = L1_PTR_BASE_ADDR;
	asm(
		// 设定段表页基地址
		"mrc  p15, 0, r0, c2, c0, 0\n"
		"mov  r0, %0\n"
		"mcr  p15, 0, r0, c2, c0, 0\n"
        // 设定16位域都为1
		"mrc  p15, 0, r0, c3, c0, 0\n"
		"mvn  r0, #0x0\n"
		"mcr  p15, 0, r0, c3, c0, 0\n"
        // 使能MMU
		"mrc  p15, 0, r0, c1, c0, 0\n"
		"orr  r0, #0x1\n"
		"mcr  p15, 0, r0, c1, c0, 0\n"
		// 空操作, 激活MMU之前的流水线上的指令清除
		"mov  r0, r0\n"
		"mov  r0, r0\n"
		"mov  r0, r0\n"
		// 输出运算符列表
		:
		// 输入运算符列表, "r"操作符表示寄存器接受baddr(%0)的值, "r"无修饰符表示只读, "=r"修饰表示可写,\
			 "+r"修饰表示可读写, "&r"修饰表示只作为输出
		:"r"(baddr)
		// 被改变资源列表
		:"r0"
	);
}

