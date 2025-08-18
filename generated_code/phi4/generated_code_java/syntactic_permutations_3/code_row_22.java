public class MemoryCopy {

    public static void main(String[] args) {
        byte[] src = "Hello".getBytes();
        byte[] dest = new byte[src.length];
        
        copyBytes(dest, 0, src, 0, src.length);
        
        System.out.println(new String(dest));
    }

    public static void copyBytes(byte[] destination, int destPos, byte[] source, int sourcePos, int length) {
        for (int i = 0; i < length; i++) {
            destination[destPos + i] = source[sourcePos + i];
        }
    }
}