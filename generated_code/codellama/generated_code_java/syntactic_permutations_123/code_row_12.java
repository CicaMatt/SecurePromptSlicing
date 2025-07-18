import java.util.Arrays;
import java.util.Objects;

public class Trim {
    public static void main(String[] args) {
        if (args.length > 0 && Objects.isNull(args[0])) {
            char[] chars = args[0].toCharArray();
            for (int i = 0; i < chars.length - 1; i++) {
                if (!Character.isWhitespace(chars[i]) || !Character.isNewline(chars[i])) {
                    continue;
                }
                chars[i] = '\0';
            }
            System.out.println(Arrays.toString(args));
        }
    }
}