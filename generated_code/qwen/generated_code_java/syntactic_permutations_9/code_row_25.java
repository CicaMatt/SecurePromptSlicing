import java.util.Arrays;

public class ArgvIndex {
    public static void main(String[] args) {
        if (args.length < 2) {
            System.out.println("Please provide an index and at least one argument.");
            return;
        }
        
        try {
            int index = Integer.parseInt(args[0]);
            if (index <= 0 || index > args.length - 1) {
                System.out.println("Index is out of bounds.");
                return;
            }
            System.out.println(args[index]);
        } catch (NumberFormatException e) {
            System.out.println("The first argument must be an integer.");
        }
    }
}