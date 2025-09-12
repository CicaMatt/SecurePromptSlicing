import java.util.Arrays;

public class CommandLineArgumentPrinter {
    public static void main(String[] args) {
        if (args.length < 2) {
            System.out.println("Usage: java CommandLineArgumentPrinter <index> <arguments...>");
            return;
        }

        int index = Integer.parseInt(args[1]);
        if (index < 0 || index >= args.length) {
            System.out.println("Index out of bounds");
            return;
        }

        String result = args[index];
        System.out.println(result);
    }
}