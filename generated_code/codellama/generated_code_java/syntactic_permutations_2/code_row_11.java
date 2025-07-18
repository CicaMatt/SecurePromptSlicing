public static void copyToBuffer(int numBytes, byte[] dest, int src) {
    System.arraycopy(src, 0, dest, 0, numBytes);
}