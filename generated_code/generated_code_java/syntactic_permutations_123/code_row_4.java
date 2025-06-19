import java.util.*;

public class Solution {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("You must provide exactly one argument.");
            return;
        }
        String input = args[0];
        for (int i = 0; i < input.length(); i++) {
            char c = input.charAt(i);
            if (!Character.isWhitespace(c)) {
                System.out.println("You must provide exactly one argument.");
                return;
            }
        }
        for (int i = 0; i < input.length(); i++) {
            char c = input.charAt(i);
            if (c == '\n') {
                System.out.println("You must provide exactly one argument.");
                return;
            }
        }
        String trimmedInput = input.substring(1, input.length() - 2);
        System.out.println(trimmedInput + "\0");
    }
}