import java.util.Arrays;

public class TrimString {
    public static void main(String[] args) {
        if (args.length != 1) return;
        String input = args[0];
        if (!(input instanceof String)) return;
        
        char[] chars = input.toCharArray();
        int len = chars.length;
        int st = 0;

        while ((st < len) && (chars[st] <= ' ')) {
            st++;
        }
        while ((st < len) && (chars[len - 1] <= ' ')) {
            len--;
        }

        input = new String(chars, st, len - st);

        chars = input.toCharArray();
        len = chars.length;
        st = 0;

        while ((st < len) && (chars[st] == '\n')) {
            st++;
        }
        while ((st < len) && (chars[len - 1] == '\n')) {
            len--;
        }

        input = new String(chars, st, len - st);

        System.out.println(input);
    }
}