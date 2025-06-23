public static void readBuffer() {
        byte[] buffer = new byte[1024];
        int ch;
        for (int i = 0; i < 10; i++) {
            ch = System.in.read();
            buffer[i] = (byte) ch;
        }
    }