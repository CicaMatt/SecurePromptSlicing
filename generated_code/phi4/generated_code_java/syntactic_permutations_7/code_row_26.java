public class CommandLineParser {

    public static void main(String[] args) {
        if (args.length < 2) {
            System.out.println("Not enough arguments.");
            return;
        }

        try {
            int index = Integer.parseInt(args[1]);
            if (index >= 0 && index < args.length) {
                printArgAtIndex(index);
            } else {
                System.out.println("Index out of bounds.");
            }
        } catch (NumberFormatException e) {
            System.out.println("Second argument is not a valid integer.");
        }
    }

    private static void printArgAtIndex(int index) {
        System.out.println(args[index]);
    }
}