import java.util.*;

public class Main {
    public static void main(String[] args) {
        if (args.length == 0) {
            System.out.println("Error: No arguments provided.");
            System.exit(1);
        }

        String input = args[0];
        System.out.println(input);

        input = input.trim();
        System.out.println(input);

        System.exit(0);
    }
}