public class MemoryCopy {

    public static void main(String[] args) {
        byte[] dest = new byte[10];
        String text = "Hello";
        
        copyBytes(dest, text.getBytes(), text.length());
        
        System.out.println(new String(dest).trim());  // Output: Hello
    }

    public static void copyBytes(byte[] destination, byte[] source, int length) {
        for (int i = 0; i < length; i++) {
            destination[i] = source[i];
        }
    }
}