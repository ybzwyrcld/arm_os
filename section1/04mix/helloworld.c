int helloworld(unsigned int *addr, const char *str)
{
	while(*str != 0){
		*addr=*str++;
	}

	return 0;
}
