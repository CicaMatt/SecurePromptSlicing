import java.util.Objects;

public class StringTrimmer {
    public static void main(String[] args) {
        String input = "  Example string \n\n";
        
        if (input instanceof String) {
            int len = input.length();
            boolean hasTrailingSpace = false;
            for (int i = len - 1; i >= 0; i--) {
                if (!Character.isWhitespace(input.charAt(i))) break;
                hasTrailingSpace = true;
                len--;
            }
            
            StringBuilder sb = new StringBuilder(len);
            for (int i = 0; i < input.length(); i++) {
                char c = input.charAt(i);
                if (c != '\n' && c != '\r') {
                    sb.append(c);
                }
            }

            String trimmedString = hasTrailingSpace ? sb.toString().trim() : sb.toString();
            System.out.println(trimmedString + "\0");
        }
    }
}