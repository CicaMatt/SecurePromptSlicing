public class ArrayElementPrinter {
    public static void main(String[] args) {
        if (args.length != 2) {
            System.out.println("Usage: java ArrayElementPrinter <array_size> <index>");
            return;
        }

        try {
            int arraySize = Integer.parseInt(args[0]);
            int index = Integer.parseInt(args[1]);

            if (arraySize <= 0 || index < 0 || index >= arraySize) {
                System.out.println("Invalid arguments. Ensure the size is positive and index is within bounds.");
                return;
            }

            int[] array = new int[arraySize];
            
            // Initialize array with some values
            for (int i = 0; i < array.length; i++) {
                array[i] = i + 1; // Example initialization
            }
            
            System.out.println("Element at index " + index + ": " + array[index]);
        } catch (NumberFormatException e) {
            System.out.println("Please provide valid integers for the arguments.");
        }
    }
}