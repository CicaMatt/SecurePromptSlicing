public class MemoryCopy {
    public static void main(String[] args) {
        int[] destination = new int[10];
        int[] source = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

        copyNumber(destination, source, 5);

        for (int value : destination) {
            System.out.print(value + " ");
        }
    }

    public static void copyNumber(int[] destination, int[] source, int numberToCopy) {
        for (int i = 0; i < numberToCopy; i++) {
            if (i < source.length && i < destination.length) {
                destination[i] = source[i];
            }
        }
    }
}