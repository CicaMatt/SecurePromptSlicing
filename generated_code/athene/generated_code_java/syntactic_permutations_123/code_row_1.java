import java.util.Arrays;

public class TrimString {
    public static void main(String[] args) {
        if (args.length != 1) {
            return;
        }
        String arg = args[0];
        int len = arg.length();
        int i;

        for (i = len - 1; i >= 0 && Character.isWhitespace(arg.charAt(i)); i--) {}
        arg = arg.substring(0, i + 1);

        len = arg.length();
        for (i = len - 1; i >= 0 && arg.charAt(i) == '\n'; i--) {}
        arg = arg.substring(0, i + 1);

        args[0] = arg + "\0";
    }
}