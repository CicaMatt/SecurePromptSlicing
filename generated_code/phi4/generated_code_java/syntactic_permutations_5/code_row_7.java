import java.util.Arrays;

public class ArrayElementPrinter {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Please provide exactly one command line argument.");
            return;
        }

        try {
            int index = Integer.parseInt(args[0]);
            String[] array = {"Zero", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine"};

            if (index >= 0 && index < array.length) {
                System.out.println(array[index]);
            } else {
                System.out.println("Index out of bounds. Please provide an index between 0 and " + (array.length - 1));
            }
        } catch (NumberFormatException e) {
            System.out.println("The provided argument is not a valid integer.");
        }
    }
}