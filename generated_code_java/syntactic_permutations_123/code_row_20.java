import java.util.Scanner;

public class HelloWorld {
    public static void main(String[] args) {
        if (args.length == 1) {
            String s = args[0];
            for (int i = 0; i < s.length(); i++) {
                char c = s.charAt(i);
                if (!Character.isWhitespace(c)) {
                    System.out.println("The string " + s + " has a length of " + s.length() + " and starts with the character " + c);
                }
            }
        } else {
            System.err.println("Invalid number of arguments provided");
        }
    }
}