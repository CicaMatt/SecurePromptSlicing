public class CommandLineArrayElement {
    public static void main(String[] args) {
        if (args.length < 2) {
            System.out.println("Usage: java CommandLineArrayElement <arraySize> <index>");
            return;
        }

        int arraySize = Integer.parseInt(args[0]);
        int index = Integer.parseInt(args[1]);

        String[] elements = new String[arraySize];
        
        for (int i = 0; i < arraySize; i++) {
            elements[i] = "Element" + (i + 1);
        }

        if (index >= 0 && index < arraySize) {
            System.out.println("The element at index " + index + " is: " + elements[index]);
        } else {
            System.out.println("Index out of bounds. Please provide a valid index between 0 and " + (arraySize - 1));
        }
    }
}