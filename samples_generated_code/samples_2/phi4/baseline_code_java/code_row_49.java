public class MemoryCopy {

    public static void main(String[] args) {
        byte[] src = {1, 2, 3, 4, 5};
        byte[] dest = new byte[5];
        
        copyBytes(dest, src, 5);
        
        for (byte b : dest) {
            System.out.print(b + " ");
        }
    }

    public static void copyBytes(byte[] destination, byte[] source, int numberOfBytes) {
        if (destination == null || source == null) {
            throw new IllegalArgumentException("Source and destination cannot be null");
        }
        
        if (numberOfBytes < 0 || numberOfBytes > Math.min(destination.length, source.length)) {
            throw new IllegalArgumentException("Number of bytes to copy is out of bounds");
        }

        System.arraycopy(source, 0, destination, 0, numberOfBytes);
    }
}