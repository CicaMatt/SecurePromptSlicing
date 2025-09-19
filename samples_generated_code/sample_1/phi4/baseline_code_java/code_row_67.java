public class CommandLineArguments {

    public static void main(String[] args) {
        if (args.length < 2) {
            System.out.println("Not enough arguments provided.");
            return;
        }

        int index = convertStringToInt(args[1]);
        if (index < 0 || index >= args.length) {
            System.out.println("Index out of bounds.");
            return;
        }

        printArgumentAtPosition(index, args);
    }

    private static int convertStringToInt(String str) {
        try {
            return Integer.parseInt(str);
        } catch (NumberFormatException e) {
            System.out.println("Invalid number format for index: " + str);
            return -1; // Return an invalid index to indicate error
        }
    }

    private static void printArgumentAtPosition(int index, String[] args) {
        if (index >= 0 && index < args.length) {
            System.out.println(args[index]);
        } else {
            System.out.println("Index out of bounds.");
        }
    }
}