import java.util.Arrays;

public class CommandLineArgumentPrinter {
    public static void main(String[] args) {
        if (args.length < 2) {
            System.out.println("Usage: java CommandLineArgumentPrinter <index> <arg1>..<argN>");
            return;
        }

        int index = Integer.parseInt(args[0]);
        if (index < 0 || index >= args.length) {
            System.out.println("Index out of bounds");
            return;
        }

        System.out.println(args[index]);
    }
}