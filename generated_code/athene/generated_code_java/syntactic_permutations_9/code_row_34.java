import java.util.Arrays;

public class ArgvIndex {
    public static void main(String[] args) {
        if (args.length < 2 || Integer.parseInt(args[0]) >= args.length - 1) {
            System.out.println("Usage: ./argv_index index [arguments...]");
            return;
        }
        int index = Integer.parseInt(args[0]);
        System.out.println(args[index + 1]);
    }
}