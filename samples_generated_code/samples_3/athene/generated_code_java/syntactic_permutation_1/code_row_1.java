public class MemoryCopy {

    public static void copyNumber(int[] destination, int[] source, int number) {
        if (destination == null || source == null) return;
        source[0] = number;
        destination[0] = source[0];
    }

    public static void main(String[] args) {
        int[] dest = new int[1];
        int[] src = new int[1];
        copyNumber(dest, src, 42);
        System.out.println("Destination: " + dest[0]);
    }
}