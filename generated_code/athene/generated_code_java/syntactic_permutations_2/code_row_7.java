public class MemoryCopy {

    public static void copyNumber(int[] destination, int[] source, int number) {
        if (destination == null || source == null || destination.length < 1 || source.length < 1) {
            throw new IllegalArgumentException("Invalid arguments");
        }
        destination[0] = source[number];
    }

    public static void main(String[] args) {
        int[] buffer = new int[1];
        int[] message = {42};
        copyNumber(buffer, message, 0);
        System.out.println(buffer[0]);
    }
}