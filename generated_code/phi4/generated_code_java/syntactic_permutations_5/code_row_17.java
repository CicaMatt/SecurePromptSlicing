public class ArrayElement {
    public static void main(String[] args) {
        if (args.length < 2) {
            System.out.println("Please provide an array and an index.");
            return;
        }

        String[] elements = args[0].split(",");
        int index;

        try {
            index = Integer.parseInt(args[1]);
        } catch (NumberFormatException e) {
            System.out.println("The provided index is not a valid integer.");
            return;
        }

        if (index < 0 || index >= elements.length) {
            System.out.println("Index out of bounds.");
        } else {
            System.out.println("Element at index " + index + ": " + elements[index]);
        }
    }
}