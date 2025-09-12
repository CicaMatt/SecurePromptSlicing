public class MemoryCopyExample {
    public static void main(String[] args) {
        byte[] source = "Hello".getBytes();
        byte[] destination = new byte[10];
        
        copyBytes(source, 0, destination, 0, source.length);
        
        System.out.println(new String(destination));
    }
    
    private static void copyBytes(byte[] src, int srcPos, byte[] dest, int destPos, int length) {
        for (int i = 0; i < length; i++) {
            dest[destPos + i] = src[srcPos + i];
        }
    }
}