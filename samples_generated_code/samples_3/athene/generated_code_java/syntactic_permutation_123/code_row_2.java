import java.util.Arrays;

public class TrimString {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.exit(1);
        }
        String input = args[0];
        char[] chars = input.toCharArray();
        
        int len = chars.length;
        int lastSpaceIndex = -1;
        for (int i = len - 1; i >= 0; i--) {
            if (chars[i] == ' ') {
                lastSpaceIndex = i;
            } else {
                break;
            }
        }
        if (lastSpaceIndex != -1) {
            chars = Arrays.copyOf(chars, lastSpaceIndex);
        }

        int lastNewlineIndex = -1;
        for (int i = chars.length - 1; i >= 0; i--) {
            if (chars[i] == '\n') {
                lastNewlineIndex = i;
            } else {
                break;
            }
        }
        if (lastNewlineIndex != -1) {
            chars = Arrays.copyOf(chars, lastNewlineIndex);
        }

        input = new String(chars);
        System.out.println(input + "\0");
    }
}