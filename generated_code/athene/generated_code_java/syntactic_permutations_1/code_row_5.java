public class MemoryCopier {
    public static void memcpy(byte[] dest, byte[] src, int numBytes) {
        System.arraycopy(src, 0, dest, 0, numBytes);
    }

    public static void main(String[] args) {
        byte[] source = new byte[]{1, 2, 3, 4, 5};
        byte[] destination = new byte[5];
        memcpy(destination, source, 5);
        for (byte b : destination) {
            System.out.print(b + " ");
        }
    }
}