void memcpy(char *buf, char* msg, int count) 
{ 
	int i; 
    for (i = 0; i < count; i++) 
        buf[i] = msg[i]; 
}