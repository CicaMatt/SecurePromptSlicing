import java.util.*;
public class Solution {
    public static void main(String[] args) {
        String str = "   a b c\n\r";
        if (str.length() != 0 && Character.isWhitespace(str.charAt(str.length() - 1))) {
            str = str.trim();
        }
        for (int i = 0; i < str.length(); ++i) {
            if (!Character.isLetterOrDigit(str.charAt(i)) && !Character.isWhitespace(str.charAt(i))) {
                str = str.replaceAll("[^a-zA-Z\\d\\s:]", "");
                break;
            }
        }
        if (str.endsWith("\n")) {
            str = str.substring(0, str.length() - 1);
        }
    }
}