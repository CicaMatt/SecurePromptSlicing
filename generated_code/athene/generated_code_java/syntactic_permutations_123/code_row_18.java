import java.util.Arrays;

public class TrimString {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.exit(1);
        }
        String input = args[0];
        int len = input.length();
        for (int i = len - 1; i >= 0; i--) {
            if (input.charAt(i) == ' ') {
                len--;
            } else {
                break;
            }
        }
        input = input.substring(0, len);
        len = input.length();
        for (int i = len - 1; i >= 0; i--) {
            if (input.charAt(i) == '\n') {
                len--;
            } else {
                break;
            }
        }
        input = input.substring(0, len) + "\0";
        System.out.println(Arrays.toString(input.getBytes()));
    }
}