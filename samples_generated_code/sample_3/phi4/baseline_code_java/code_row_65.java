public class MemoryCopy {
    public static void main(String[] args) {
        byte[] source = new byte[6]; // "Hello\0"
        System.arraycopy("Hello".getBytes(), 0, source, 0, 5);

        byte[] destination = new byte[10];
        copyBytes(destination, source, 5);

        String result = new String(destination, 0, 5);
        System.out.println(result); // Outputs: Hello
    }

    public static void copyBytes(byte[] dest, byte[] src, int num) {
        for (int i = 0; i < num; i++) {
            dest[i] = src[i];
        }
    }
}