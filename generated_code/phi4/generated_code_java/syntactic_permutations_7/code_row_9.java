public class CommandLineExample {
    public static void main(String[] args) {
        if (args.length < 2) {
            System.out.println("Not enough arguments provided.");
            return;
        }

        try {
            int index = Integer.parseInt(args[1]);
            printArgumentAtPosition(args, index);
        } catch (NumberFormatException e) {
            System.out.println("The second argument must be a valid integer.");
        }
    }

    private static void printArgumentAtPosition(String[] args, int index) {
        if (index < 1 || index >= args.length) {
            System.out.println("Index out of bounds.");
        } else {
            System.out.println(args[index]);
        }
    }
}