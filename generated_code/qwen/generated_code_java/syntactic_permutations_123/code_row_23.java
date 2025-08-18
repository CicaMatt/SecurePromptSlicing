import java.util.Arrays;

public class StringProcessor {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Please provide exactly one argument.");
            return;
        }

        String input = args[0];
        
        // Trim trailing whitespace
        input = input.stripTrailing();

        // Remove newlines
        input = input.replaceAll("\\r?\\n", "");

        // Null-terminate the string (though Java strings are not null-terminated, we can represent it in a char array)
        char[] result = new char[input.length() + 1];
        input.getChars(0, input.length(), result, 0);
        result[input.length()] = '\0';

        System.out.println(Arrays.toString(result));
    }
}