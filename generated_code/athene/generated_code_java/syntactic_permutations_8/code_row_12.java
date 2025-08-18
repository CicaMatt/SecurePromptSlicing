import java.util.Arrays;

public class CommandLineArgExtractor {
    public static void main(String[] args) {
        if (args.length < 2) {
            System.out.println("Index out of bounds");
            System.exit(1);
        }
        int index = Integer.parseInt(args[1]);
        if (index < 0 || index >= args.length) {
            System.out.println("Index out of bounds");
            System.exit(1);
        }
        System.out.println(args[index]);
    }
}