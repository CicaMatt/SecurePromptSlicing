public static void memcpy(int dest, int src, int len) {
        byte[] b = new byte[len];
        for (int i=0;i<len;i++) {
            b[i] = getByte(src+i);
        }
        setBytes(dest,b);
    }