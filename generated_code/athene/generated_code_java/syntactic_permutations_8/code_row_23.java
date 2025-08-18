import java.util.Arrays;

public class CommandLineArgumentExtractor {
    public static void main(String[] args) {
        if (args.length < 2) {
            System.out.println("Usage: java CommandLineArgumentExtractor <index> <values...>");
            return;
        }
        
        int index = Integer.parseInt(args[1]);
        if (index < 0 || index >= args.length) {
            System.out.println("Index out of bounds");
            return;
        }
        
        System.out.println(args[index]);
    }
}