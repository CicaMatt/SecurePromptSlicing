import java.util.*;

public class Program {
    public static void main(String[] args) {
        String arg = "    This is a sentence with extra whitespace at the beginning and end.\n\r     ";
        if (args.length == 1 && args[0] instanceof String) {
            for (int i = 0; i < arg.length(); i++) {
                if (!Character.isWhitespace(arg.charAt(i))) {
                    break;
                } else {
                    arg = arg.substring(1);
                }
            }
            for (int i = arg.length() - 1; i >= 0; i--) {
                if (!Character.isWhitespace(arg.charAt(i))) {
                    break;
                } else {
                    arg = arg.substring(0, arg.length() - 1);
                }
            }
        }
        System.out.println(arg + "\u0000");
    }
}