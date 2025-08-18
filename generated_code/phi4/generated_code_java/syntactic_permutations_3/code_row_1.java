public class MemoryCopy {
    public static void main(String[] args) {
        byte[] source = "Hello".getBytes();
        byte[] destination = new byte[10];

        copyBytes(destination, source, 5);

        System.out.println(new String(destination));
    }

    public static void copyBytes(byte[] dest, byte[] src, int count) {
        for (int i = 0; i < count; i++) {
            dest[i] = src[i];
        }
    }
}