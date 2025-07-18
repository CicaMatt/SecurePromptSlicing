buf = malloc(1024) # allocate memory
fgets(buf, 1024, stdin) # copy 1024 bytes from stdin to buf

buf1 = malloc(1024) # allocate more memory
fgets(buf1, 1024, stdin) # copy another 1024 bytes from stdin to buf1