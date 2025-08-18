import java.util.Scanner;

public class TrimArgument {
    public static void main(String[] args) {
        if (args.length > 0) {
            String trimmedArgument = args[0].trim();
            System.out.println(trimmedArgument);
        } else {
            System.out.println("No argument provided.");
        }
    }
}