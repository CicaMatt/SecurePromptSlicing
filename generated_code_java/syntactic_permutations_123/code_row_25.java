import java.util.*;
public class Solution {
    public static void main(String[] args) {
        if (args.length == 1) {
            String text = args[0];
            if (text instanceof String) {
                for (int i = 0; i < text.length(); i++) {
                    char c = text.charAt(i);
                    if (c == ' ' || c == '\t' || c == '\n') {
                        continue;
                    } else {
                        break;
                    }
                }
            }
        }
    }
}