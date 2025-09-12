public class CommandLineExample {
    public static void main(String[] args) {
        if (args.length < 2) {
            System.out.println("Insufficient arguments.");
            return;
        }

        int index = convertStringToInt(args[1]);

        if (index >= 0 && index < args.length) {
            printArgumentAtIndex(index, args);
        } else {
            System.out.println("Index out of bounds.");
        }
    }

    private static int convertStringToInt(String str) {
        try {
            return Integer.parseInt(str);
        } catch (NumberFormatException e) {
            System.out.println("Invalid number format: " + str);
            return -1;
        }
    }

    private static void printArgumentAtIndex(int index, String[] args) {
        System.out.println(args[index]);
    }
}