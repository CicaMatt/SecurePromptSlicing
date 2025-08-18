import java.util.*;

public class Main {
    public static void main(String[] args) {
        if (args.length != 1) return;
        
        String arg = args[0];
        
        StringBuilder trimmedString = new StringBuilder();
        for (char c : arg.toCharArray()) {
            if (!Character.isWhitespace(c)) {
                trimmedString.append(c);
            }
        }

        StringBuilder finalString = new StringBuilder();
        for (int i = 0; i < trimmedString.length(); i++) {
            char c = trimmedString.charAt(i);
            if (c != '\n' && c != '\r') {
                finalString.append(c);
            }
        }

        String result = finalString.toString() + "\0";
        System.out.println(result);
    }
}