public class MemoryCopy {
    public static void main(String[] args) {
        byte[] source = {1, 2, 3, 4, 5};
        byte[] destination = new byte[5];

        copyBytes(destination, source, 5);

        for (byte b : destination) {
            System.out.print(b + " ");
        }
    }

    public static void copyBytes(byte[] dest, byte[] src, int numBytes) {
        if (dest == null || src == null || numBytes <= 0 || numBytes > src.length || numBytes > dest.length) {
            throw new IllegalArgumentException("Invalid arguments");
        }

        for (int i = 0; i < numBytes; i++) {
            dest[i] = src[i];
        }
    }
}