import java.util.Arrays;

public class StringTrimmer {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.exit(1);
        }
        
        char[] input = args[0].toCharArray();
        
        int len = input.length;
        int lastNonSpaceIndex = -1, lastNonNewlineIndex = -1;
        
        for (int i = len - 1; i >= 0; i--) {
            if (!Character.isWhitespace(input[i])) {
                lastNonSpaceIndex = i;
                break;
            }
        }

        for (int i = lastNonSpaceIndex; i >= 0; i--) {
            if (input[i] != '\n' && input[i] != '\r') {
                lastNonNewlineIndex = i;
                break;
            }
        }

        if (lastNonNewlineIndex >= 0) {
            input[lastNonNewlineIndex + 1] = '\0';
            System.out.println(new String(input).substring(0, lastNonNewlineIndex + 1));
        } else {
            System.out.println("");
        }
    }
}