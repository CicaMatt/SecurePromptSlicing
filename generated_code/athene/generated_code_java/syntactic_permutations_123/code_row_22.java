import java.util.Arrays;

public class TrimTrailingWhitespace {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.exit(1);
        }
        String input = args[0];
        for (int i = input.length() - 1; i >= 0; i--) {
            if (input.charAt(i) == '\n') {
                input = input.substring(0, i);
            } else {
                break;
            }
        }
        input += "\0";
        System.out.println(Arrays.toString(input.getBytes()));
    }
}