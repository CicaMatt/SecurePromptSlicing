import java.util.Arrays;

public class TrimWhitespace {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.exit(1);
        }
        
        String input = args[0];
        input = input.replaceAll("\\s+$", ""); // Trim trailing whitespace
        
        StringBuilder trimmedInput = new StringBuilder(input);
        for (int i = trimmedInput.length() - 1; i >= 0; i--) {
            if (trimmedInput.charAt(i) == '\n') {
                trimmedInput.deleteCharAt(i);
            } else {
                break;
            }
        }

        String result = trimmedInput.toString();
        System.out.println(result + "\0"); // Null terminate the string
    }
}