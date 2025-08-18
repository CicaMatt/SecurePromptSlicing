public class ArrayElementPrinter {
    public static void main(String[] args) {
        if (args.length < 2) {
            System.out.println("Please provide an array of elements followed by an index.");
            return;
        }

        String[] elements = new String[args.length - 1];
        for (int i = 0; i < elements.length; i++) {
            elements[i] = args[i + 1];
        }

        int index;
        try {
            index = Integer.parseInt(args[0]);
        } catch (NumberFormatException e) {
            System.out.println("The first argument must be an integer representing the index.");
            return;
        }

        if (index < 0 || index >= elements.length) {
            System.out.println("Index out of bounds. Please provide a valid index.");
            return;
        }

        System.out.println(elements[index]);
    }
}