import java.util.*;
public class Main {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Error: You must provide one argument.");
            System.exit(1);
        }
        String input = args[0];
        System.out.println(input);
        String trimmedInput = input.trim();
        System.out.println(trimmedInput);
    }
}