public static void copyMemory(byte[] destination, byte[] source, int numBytes) {
        System.arraycopy(source, 0, destination, 0, numBytes);
    }