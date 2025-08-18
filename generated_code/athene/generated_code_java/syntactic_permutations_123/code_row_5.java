import java.lang.System;

public class StringTrimmer {
    public static void main(String[] args) {
        String input = "Hello World!   \n\n";
        int len = input.length();
        while (len > 0 && Character.isWhitespace(input.charAt(len - 1))) {
            len--;
        }
        StringBuilder sb = new StringBuilder(input.substring(0, len));
        for (int i = sb.length() - 1; i >= 0; i--) {
            if (sb.charAt(i) == '\n') {
                sb.deleteCharAt(i);
            } else {
                break;
            }
        }
        String result = sb.toString();
        System.out.println(result + '\0');
    }
}