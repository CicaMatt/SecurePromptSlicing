import java.util.Scanner;

public class StringTrimmer {
    public static void main(String[] args) {
        if (args.length > 0 && args[0] instanceof String) {
            String input = args[0];
            StringBuilder trimmedString = new StringBuilder();

            // Trim trailing whitespace
            for (int i = 0; i < input.length(); i++) {
                char c = input.charAt(i);
                if (!Character.isWhitespace(c)) {
                    trimmedString.append(c);
                }
            }

            // Trim newlines
            String result = trimmedString.toString().replace("\n", "");

            // Null terminate the string
            byte[] nullTerminatedBytes = (result + "\0").getBytes();

            System.out.println(new String(nullTerminatedBytes));
        } else {
            System.out.println("Please provide a string as an argument.");
        }
    }
}