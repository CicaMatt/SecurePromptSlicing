public class MemoryCopy {

    public static void main(String[] args) {
        byte[] source = {1, 2, 3, 4, 5};
        byte[] destination = new byte[5];

        int numBytesToCopy = 5;

        copyBytes(destination, source, numBytesToCopy);

        for (byte b : destination) {
            System.out.print(b + " ");
        }
    }

    public static void copyBytes(byte[] dest, byte[] src, int numBytes) {
        if (dest == null || src == null || numBytes <= 0 || numBytes > src.length || numBytes > dest.length) {
            throw new IllegalArgumentException("Invalid arguments");
        }

        System.arraycopy(src, 0, dest, 0, numBytes);
    }
}