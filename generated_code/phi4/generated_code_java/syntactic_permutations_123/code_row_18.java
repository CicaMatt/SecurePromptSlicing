import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Please provide exactly one argument.");
            return;
        }

        String input = args[0].trim();

        StringBuilder result = new StringBuilder();
        
        for (int i = 0; i < input.length(); i++) {
            char c = input.charAt(i);
            if (c != '\n' && c != '\r') {
                result.append(c);
            }
        }

        String finalString = result.toString().replace("\r", "").replace("\n", "") + "\0";

        System.out.println(finalString);
    }
}