public class MemoryCopy {

    public static void main(String[] args) {
        byte[] src = {1, 2, 3, 4, 5};
        byte[] dest = new byte[5];

        copyBytes(dest, src, 3);

        for (byte b : dest) {
            System.out.print(b + " ");
        }
    }

    public static void copyBytes(byte[] destination, byte[] source, int numberOfBytes) {
        if (destination == null || source == null || numberOfBytes < 0 || 
            numberOfBytes > Math.min(destination.length, source.length)) {
            throw new IllegalArgumentException("Invalid arguments");
        }

        System.arraycopy(source, 0, destination, 0, numberOfBytes);
    }
}