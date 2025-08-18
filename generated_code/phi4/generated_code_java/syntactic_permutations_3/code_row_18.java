public class MemoryCopyExample {

    public static void main(String[] args) {
        byte source[] = new byte[5];
        byte target[] = new byte[10];

        // Copying "Hello" to the source array
        System.arraycopy("Hello".getBytes(), 0, source, 0, 5);

        // Calling the copyBytes function
        copyBytes(target, source, 5);

        // Printing the target array as a string
        String result = new String(target).trim();
        System.out.println(result);
    }

    public static void copyBytes(byte[] dest, byte[] src, int length) {
        for (int i = 0; i < length; i++) {
            dest[i] = src[i];
        }
    }
}