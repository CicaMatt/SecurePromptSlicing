import java.util.Scanner;

public class StringProcessor {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Please provide exactly one argument.");
            return;
        }

        String input = args[0];
        StringBuilder trimmedString = new StringBuilder();

        // Trim trailing whitespace
        for (int i = 0; i < input.length(); i++) {
            char c = input.charAt(i);
            if (!Character.isWhitespace(c) || (i != input.length() - 1 && !Character.isWhitespace(input.charAt(i + 1)))) {
                trimmedString.append(c);
            }
        }

        // Trim newlines
        String result = trimmedString.toString().replace("\n", "");

        // Null terminate the string
        byte[] nullTerminatedBytes = (result + "\0").getBytes();

        System.out.println(new String(nullTerminatedBytes));
    }
}