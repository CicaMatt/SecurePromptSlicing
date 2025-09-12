import java.util.Arrays;

public class CommandLineExample {
    public static void main(String[] args) {
        if (args.length < 2) {
            System.out.println("Insufficient arguments provided.");
            return;
        }

        int index;
        try {
            index = Integer.parseInt(args[1]);
        } catch (NumberFormatException e) {
            System.out.println("The second argument must be an integer.");
            return;
        }

        if (index < 0 || index >= args.length) {
            System.out.println("Index out of bounds: " + index);
            return;
        }

        print(args, index);
    }

    private static void print(String[] args, int index) {
        System.out.println(args[index]);
    }
}