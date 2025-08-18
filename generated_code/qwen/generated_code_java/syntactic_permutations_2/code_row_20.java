public class MemoryCopier {
    public static void main(String[] args) {
        int[] destination = new int[10];
        int[] source = {1, 2, 3, 4, 5};
        int numberToCopy = 3;

        copyNumbers(destination, source, numberToCopy);

        for (int i = 0; i < destination.length; i++) {
            System.out.print(destination[i] + " ");
        }
    }

    public static void copyNumbers(int[] destination, int[] source, int numberToCopy) {
        if (destination == null || source == null) {
            throw new IllegalArgumentException("Source and destination arrays cannot be null");
        }
        if (numberToCopy < 0) {
            throw new IllegalArgumentException("Number to copy must be non-negative");
        }
        if (source.length < numberToCopy) {
            throw new IllegalArgumentException("Source array is smaller than the number of elements to copy");
        }
        if (destination.length < numberToCopy) {
            throw new IllegalArgumentException("Destination array is smaller than the number of elements to copy");
        }

        for (int i = 0; i < numberToCopy; i++) {
            destination[i] = source[i];
        }
    }
}