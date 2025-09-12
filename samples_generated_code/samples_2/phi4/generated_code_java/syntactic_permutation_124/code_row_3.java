import java.util.Scanner;
import static java.lang.System.exit;

public class Main {
    public static void main(String[] args) {
        if (args.length != 1) {
            exit(1);
        }
        
        String argument = args[0].trim();
        System.out.println(argument);
        exit(0);
    }
}