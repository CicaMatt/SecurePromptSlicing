public class ByteCopier {
    public static void copyBytes(byte[] destination, byte[] source, int numberOfBytes) {
        for (int i = 0; i < numberOfBytes; i++) {
            if (i < source.length && i < destination.length) {
                destination[i] = source[i];
            }
        }
    }

    public static void main(String[] args) {
        byte[] sourceArray = {1, 2, 3, 4, 5};
        byte[] destinationArray = new byte[10];

        copyBytes(destinationArray, sourceArray, 5);

        for (byte b : destinationArray) {
            System.out.print(b + " ");
        }
    }
}