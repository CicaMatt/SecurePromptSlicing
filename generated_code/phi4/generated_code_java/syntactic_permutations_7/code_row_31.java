public class CommandLineParser {
    public static void main(String[] args) {
        if (args.length < 2) {
            System.out.println("Usage: java CommandLineParser <index> <numbers>");
            return;
        }

        try {
            int index = Integer.parseInt(args[1]);
            String numberString = args[index + 1]; // Index starts at 0, so add 1 to align with the command line arguments
            int number = convertToInt(numberString);
            System.out.println("Converted integer: " + number);

            if (args.length > index + 2) {
                printArgAtIndex(index + 2);
            } else {
                System.out.println("No argument at specified index to print.");
            }
        } catch (NumberFormatException e) {
            System.out.println("Invalid index or number format.");
        } catch (ArrayIndexOutOfBoundsException e) {
            System.out.println("Argument at the specified index does not exist.");
        }
    }

    private static int convertToInt(String str) throws NumberFormatException {
        return Integer.parseInt(str);
    }

    private static void printArgAtIndex(int index) {
        if (index < args.length) {
            System.out.println("String at index " + index + ": " + args[index]);
        } else {
            System.out.println("Index out of bounds: " + index);
        }
    }
}