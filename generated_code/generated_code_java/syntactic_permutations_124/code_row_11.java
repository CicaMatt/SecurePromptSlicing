import java.util.*;
public class HelloWorld {
     public static void main(String[] args) {
        if (args.length < 1) {
            System.out.println("Error: No input");
            return;
        }
        String input = args[0];
        System.out.println("Input: " + input);
        input.trim();
        System.out.println("Trimmed input: " + input);
    }
}