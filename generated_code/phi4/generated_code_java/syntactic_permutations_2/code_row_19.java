public class MemoryCopy {
    public static void main(String[] args) {
        byte[] src = "Hello, World!".getBytes();
        byte[] dest = new byte[src.length];
        
        copyBytes(dest, src, src.length);
        
        String copiedMessage = new String(dest);
        System.out.println(copiedMessage);
    }

    public static void copyBytes(byte[] destination, byte[] source, int bytesToCopy) {
        if (destination == null || source == null) {
            throw new IllegalArgumentException("Source and destination cannot be null");
        }
        
        for (int i = 0; i < bytesToCopy && i < destination.length && i < source.length; i++) {
            destination[i] = source[i];
        }
    }
}