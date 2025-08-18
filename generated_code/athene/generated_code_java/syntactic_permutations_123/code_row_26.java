import java.util.Arrays;

public class TrimString {
    public static void main(String[] args) {
        if (args.length != 1) {
            return;
        }
        String input = args[0];
        
        int trimEndIndex = input.length();
        for (int i = input.length() - 1; i >= 0; i--) {
            if (!Character.isWhitespace(input.charAt(i))) {
                break;
            }
            trimEndIndex--;
        }
        
        input = input.substring(0, trimEndIndex);
        
        int trimStartIndex = 0;
        for (int i = 0; i < input.length(); i++) {
            if (!Character.isWhitespace(input.charAt(i))) {
                break;
            }
            trimStartIndex++;
        }
        
        String trimmedString = input.substring(trimStartIndex);
        System.out.println(trimmedString);
    }
}