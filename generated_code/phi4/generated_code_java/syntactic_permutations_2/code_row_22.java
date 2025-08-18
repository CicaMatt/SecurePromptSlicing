public class MemoryCopier {

    public static void main(String[] args) {
        byte[] src = {1, 2, 3, 4, 5};
        byte[] dest = new byte[10];
        
        // Copy first 3 bytes from src to dest
        copyBytes(dest, src, 3);
        
        for (byte b : dest) {
            System.out.print(b + " ");
        }
    }

    public static void copyBytes(byte[] destination, byte[] source, int length) {
        if (destination == null || source == null) {
            throw new IllegalArgumentException("Source and destination cannot be null");
        }
        
        if (length < 0 || length > source.length || length > destination.length) {
            throw new IllegalArgumentException("Invalid number of bytes to copy");
        }

        System.arraycopy(source, 0, destination, 0, length);
    }
}