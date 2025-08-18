public class ByteCopier {

    public static void main(String[] args) {
        byte[] source = {1, 2, 3, 4, 5};
        byte[] destination = new byte[5];

        copyBytes(destination, source, 5);

        for (byte b : destination) {
            System.out.print(b + " ");
        }
    }

    public static void copyBytes(byte[] dest, byte[] src, int length) {
        if (dest == null || src == null || length <= 0) {
            throw new IllegalArgumentException("Invalid arguments");
        }
        
        for (int i = 0; i < length; i++) {
            dest[i] = src[i];
        }
    }
}