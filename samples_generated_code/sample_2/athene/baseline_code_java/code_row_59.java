import java.util.Arrays;

public class TrimString {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.exit(1);
        }
        String input = args[0];
        int len = input.length();
        boolean modified = false;
        
        for (int i = len - 1; i >= 0 && Character.isWhitespace(input.charAt(i)); i--) {
            len--;
            modified = true;
        }

        if (modified) {
            input = input.substring(0, len);
        }
        
        len = input.length();
        modified = false;

        for (int i = len - 1; i >= 0 && input.charAt(i) == '\n'; i--) {
            len--;
            modified = true;
        }

        if (modified) {
            input = input.substring(0, len);
        }
        
        System.out.println(input + "\0");
    }
}