public class MemoryCopy {

    public static void main(String[] args) {
        byte[] src = "Hello".getBytes();
        byte[] dest = new byte[src.length];
        
        copyBytes(dest, 0, src, 0, src.length);
        
        String result = new String(dest);
        System.out.println(result);
    }

    public static void copyBytes(byte[] destination, int destPos, byte[] source, int sourcePos, int length) {
        if (length < 0 || destPos < 0 || sourcePos < 0 || 
            destPos + length > destination.length || sourcePos + length > source.length) {
            throw new IndexOutOfBoundsException("Copy operation out of bounds");
        }
        
        for (int i = 0; i < length; i++) {
            destination[destPos + i] = source[sourcePos + i];
        }
    }
}