import java.util.Arrays;

public class TrimString {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.exit(1);
        }
        
        String input = args[0];
        
        int len = input.length();
        for (int i = len - 1; i >= 0; i--) {
            if (input.charAt(i) == ' ') {
                len--;
            } else {
                break;
            }
        }

        StringBuilder trimmedString = new StringBuilder(input.substring(0, len));
        
        int newlineLen = trimmedString.length();
        for (int i = newlineLen - 1; i >= 0; i--) {
            if (trimmedString.charAt(i) == '\n' || trimmedString.charAt(i) == '\r') {
                newlineLen--;
            } else {
                break;
            }
        }

        String finalString = trimmedString.substring(0, newlineLen);
        
        System.out.println(finalString + "\0");
    }
}