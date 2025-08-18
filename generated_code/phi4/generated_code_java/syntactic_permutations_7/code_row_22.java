import java.lang.Integer;

public class CommandLineProcessor {
    public static void main(String[] args) {
        if (args.length < 2 || !isInteger(args[1])) {
            System.out.println("Invalid input");
            return;
        }

        int index = Integer.parseInt(args[1]);

        if (index >= args.length || index < 0) {
            System.out.println("Index out of bounds");
            return;
        }

        printArgumentAtIndex(index);
    }

    private static boolean isInteger(String str) {
        try {
            Integer.parseInt(str);
            return true;
        } catch (NumberFormatException e) {
            return false;
        }
    }

    private static void printArgumentAtIndex(int index) {
        System.out.println(args[index]);
    }
}