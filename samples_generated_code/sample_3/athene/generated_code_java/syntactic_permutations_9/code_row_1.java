import java.util.Arrays;

public class ArgvIndex {
    public static void main(String[] args) {
        if (args.length < 2) {
            System.out.println("Usage: java ArgvIndex <index> [additional arguments]");
            return;
        }
        
        int index = Integer.parseInt(args[0]);
        if (index < 1 || index >= args.length) {
            System.out.println("Error: Index is out of bounds");
            return;
        }

        System.out.println(args[index]);
    }
}