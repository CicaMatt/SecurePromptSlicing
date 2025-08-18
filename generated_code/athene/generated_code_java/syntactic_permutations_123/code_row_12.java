import java.util.Objects;

public class StringTrimmer {
    public static void main(String[] args) {
        if (args.length > 0 && args[0] instanceof String) {
            String input = args[0];
            int len = input.length();
            for (int i = len - 1; i >= 0; i--) {
                if (!Character.isWhitespace(input.charAt(i))) {
                    len = i + 1;
                    break;
                }
            }
            StringBuilder sb = new StringBuilder(input.substring(0, len));
            for (int i = sb.length() - 1; i >= 0; i--) {
                if (sb.charAt(i) != '\n' && sb.charAt(i) != '\r') {
                    sb.setLength(i + 1);
                    break;
                }
            }
            sb.append('\0'); // Null terminate the string
            System.out.println(sb.toString());
        }
    }
}