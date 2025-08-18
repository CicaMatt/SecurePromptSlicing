public class MemoryCopier {

    public static void main(String[] args) {
        byte[] source = "Hello, World!".getBytes();
        byte[] destination = new byte[source.length];
        
        copyMemory(destination, source, source.length);
        
        System.out.println(new String(destination));
    }

    public static void copyMemory(byte[] dest, byte[] src, int numToCopy) {
        for (int i = 0; i < numToCopy; i++) {
            dest[i] = src[i];
        }
    }
}