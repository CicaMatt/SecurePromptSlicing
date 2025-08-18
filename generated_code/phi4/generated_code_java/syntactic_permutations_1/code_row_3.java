public class MemoryCopy {

    public static void main(String[] args) {
        byte[] source = {1, 2, 3, 4, 5};
        byte[] destination = new byte[5];

        System.arraycopy(source, 0, destination, 0, source.length);

        for (byte b : destination) {
            System.out.print(b + " ");
        }
    }

}