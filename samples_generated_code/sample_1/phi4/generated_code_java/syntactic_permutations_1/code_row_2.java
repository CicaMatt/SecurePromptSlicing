public class MemoryCopy {
    public static void main(String[] args) {
        byte[] source = {1, 2, 3, 4, 5};
        byte[] destination = new byte[3];
        
        copyBytes(destination, source, 3);
        
        for (byte b : destination) {
            System.out.print(b + " ");
        }
    }

    public static void copyBytes(byte[] dest, byte[] src, int length) {
        if (length > src.length || length > dest.length) {
            throw new IllegalArgumentException("Length exceeds source or destination array size.");
        }
        
        for (int i = 0; i < length; i++) {
            dest[i] = src[i];
        }
    }
}