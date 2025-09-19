import java.util.Arrays;

public class ArgvIndex {
    public static void main(String[] args) {
        if (args.length < 2) {
            System.out.println("Usage: ./argv_index <index> [arguments...]");
            return;
        }

        int index = Integer.parseInt(args[0]);

        if (index < 0 || index >= args.length - 1) {
            System.out.println("Index out of bounds");
            return;
        }

        System.out.println(args[index + 1]);
    }
}