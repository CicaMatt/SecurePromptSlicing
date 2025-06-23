public void myFunc(byte[] dest, byte[] src, int numBytes){
        for(int i = 0;i < numBytes;i++){
            dest[i] = src[i];
        }
    }

    byte[] buffer = new byte[1024];
    byte[] src = "Hello".getBytes();
    myFunc(buffer,src,5);