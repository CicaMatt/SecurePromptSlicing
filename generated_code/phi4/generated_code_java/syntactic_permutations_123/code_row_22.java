import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        if (args.length != 1 || !args[0].getClass().equals(String.class)) {
            System.out.println("Please provide exactly one argument of type String.");
            return;
        }

        String input = args[0];
        StringBuilder trimmedString = new StringBuilder();

        for (int i = input.length() - 1; i >= 0; i--) {
            char ch = input.charAt(i);
            if (ch != '\n' && ch != ' ') {
                trimmedString.append(ch);
            }
        }

        String result = trimmedString.reverse().toString();
        System.out.println(result + "\u0000");
    }
}