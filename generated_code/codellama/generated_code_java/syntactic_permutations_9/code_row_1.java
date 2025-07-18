import java.util.Arrays;

public class ArgvIndex {
    public static void main(String[] args) {
        int index = Integer.parseInt(args[0]); // parseInt parses a string as an integer, throws exception otherwise
        if (index < 1 || index >= args.length) { // validate the input argument is within range
            System.out.println("Invalid index.");
        } else {
            String arg = args[index];
            System.out.println(arg);
        }
    }
}