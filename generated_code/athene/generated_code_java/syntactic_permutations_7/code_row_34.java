import java.util.Arrays;

public class CommandLineIndex {
    public static void main(String[] args) {
        if (args.length < 2) {
            System.exit(1);
        }
        int index = Integer.parseInt(args[1]);
        if (index < 0 || index >= args.length) {
            System.exit(1);
        }
        System.out.println(args[index]);
    }
}