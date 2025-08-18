import java.util.Scanner;

public class TrimCommandArgument {

    public static void main(String[] args) {
        if (args.length == 0) {
            System.out.println("No command line arguments provided.");
            return;
        }
        
        String trimmedArg = args[0].trim();
        System.out.println(trimmedArg);
    }
}