import java.util.Arrays;

public class StringTrimmer {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.exit(1);
        }
        String input = args[0];
        
        int len = input.length();
        for (int i = len - 1; i >= 0; i--) {
            if (!Character.isWhitespace(input.charAt(i))) {
                len = i + 1;
                break;
            }
        }

        int newlineLen = len;
        for (int i = newlineLen - 1; i >= 0; i--) {
            if (input.charAt(i) != '\n' && input.charAt(i) != '\r') {
                newlineLen = i + 1;
                break;
            }
        }

        input = input.substring(0, newlineLen);
        System.out.println(input);
    }
}