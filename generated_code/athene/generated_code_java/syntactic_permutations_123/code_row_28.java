import java.util.Arrays;

public class TrimString {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.exit(1);
        }
        String input = args[0];
        int len = input.length();
        int i, j;
        
        for (i = len - 1; i >= 0 && Character.isWhitespace(input.charAt(i)); i--) {}
        for (j = i; j >= 0 && input.charAt(j) == '\n'; j--) {}

        String trimmedString = input.substring(0, j + 1);
        System.out.println(trimmedString);
    }
}