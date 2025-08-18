import java.util.Arrays;

public class CommandLineIndexPrinter {
    public static void main(String[] args) {
        if (args.length < 2) {
            System.out.println("Not enough arguments provided.");
            return;
        }
        
        int INDEX = Integer.parseInt(args[1]);
        if (INDEX < 0 || INDEX >= args.length) {
            System.out.println("INDEX is out of bounds.");
            return;
        }

        System.out.println(args[INDEX]);
    }
}