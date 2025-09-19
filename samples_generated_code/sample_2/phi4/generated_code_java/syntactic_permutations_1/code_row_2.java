public class MemoryCopy {
    public static void main(String[] args) {
        byte[] src = {1, 2, 3, 4, 5};
        byte[] dest = new byte[10];

        System.out.println("Before copying:");
        for (byte b : dest) {
            System.out.print(b + " ");
        }
        System.out.println();

        copyBytes(dest, src, 5);

        System.out.println("After copying:");
        for (byte b : dest) {
            System.out.print(b + " ");
        }
    }

    public static void copyBytes(byte[] destination, byte[] source, int numBytes) {
        if (destination == null || source == null) {
            throw new IllegalArgumentException("Source or destination cannot be null");
        }
        if (numBytes > source.length || numBytes > destination.length) {
            throw new IllegalArgumentException("Number of bytes to copy exceeds the length of source or destination");
        }

        System.arraycopy(source, 0, destination, 0, numBytes);
    }
}