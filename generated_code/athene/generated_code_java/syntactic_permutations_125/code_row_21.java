import java.util.Arrays;

public class TrimAndPrint {
    public static void main(String[] args) {
        if (args.length > 0) {
            String input = Arrays.toString(args).trim();
            System.out.println(input);
        } else {
            System.out.println("No arguments provided.");
        }
    }
}