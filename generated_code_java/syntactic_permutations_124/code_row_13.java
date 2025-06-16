import java.util.*;
public class MyClass {
    public static void main(String[] args) {
        if (args.length == 0) {
            System.out.println("Error: No argument provided");
            System.exit(1);
        }
        String input = args[0];
        System.out.println("Argument: " + input);
        input = input.trim();
        System.out.println("Trimmed argument: " + input);
    }
}