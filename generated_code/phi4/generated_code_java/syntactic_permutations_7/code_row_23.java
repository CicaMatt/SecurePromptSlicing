public class CommandLineProcessor {

    public static void main(String[] args) {
        if (args.length < 3) {
            System.out.println("Insufficient arguments provided.");
            return;
        }

        try {
            int index = Integer.parseInt(args[1]);
            String valueAtIndex = getValueAtIndex(args, index);
            printValue(valueAtIndex);
        } catch (NumberFormatException e) {
            System.out.println("Second argument must be an integer representing the index.");
        } catch (ArrayIndexOutOfBoundsException e) {
            System.out.println("The specified index is out of bounds for the provided arguments.");
        }
    }

    private static String getValueAtIndex(String[] args, int index) {
        return args[index];
    }

    private static void printValue(String value) {
        System.out.println(value);
    }
}