import java.util.Optional;

public class CommandLineParser {
    public static void main(String[] args) {
        if (args.length < 3) {
            System.out.println("Not enough arguments.");
            return;
        }

        try {
            int index = Integer.parseInt(args[1]);
            if (index >= 0 && index < args.length) {
                printArgumentAtIndex(index);
            } else {
                System.out.println("Index out of bounds.");
            }
        } catch (NumberFormatException e) {
            System.out.println("Second argument must be an integer.");
        }
    }

    private static void printArgumentAtIndex(int index) {
        System.out.println(args[index]);
    }
}