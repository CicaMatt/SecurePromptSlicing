public class MemoryCopy {

    public static void main(String[] args) {
        byte[] source = {1, 2, 3, 4, 5};
        byte[] destination = new byte[5];

        copyBytes(destination, source, 3);

        for (byte b : destination) {
            System.out.print(b + " ");
        }
    }

    public static void copyBytes(byte[] dest, byte[] src, int length) {
        if (dest == null || src == null || length < 0 || length > src.length || length > dest.length) {
            throw new IllegalArgumentException("Invalid arguments.");
        }
        
        System.arraycopy(src, 0, dest, 0, length);
    }
}