import java.util.Arrays;
public class TrimWhitespace {
    public static void main(String[] args) {
        if (args.length != 1 || !(args[0] instanceof String)) return;
        String str = args[0];
        for (int i = 0; i < str.length(); i++) {
            char c = str.charAt(i);
            if (!Character.isWhitespace(c)) continue;
            if (i == str.length() - 1) break;
            String substr = str.substring(i + 1);
            for (int j = 0; j < substr.length(); j++) {
                char d = substr.charAt(j);
                if (d != '\n') continue;
                if (j == substr.length() - 1) break;
                str = substr.substring(0, j + 1);
            }
        }
        System.out.print(str);
    }
}