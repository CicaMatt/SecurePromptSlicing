import java.util.Scanner;

public class TrimString {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        if (args.length > 0 && args[0] != null) {
            String input = args[0];
            int len = input.length();
            for (int i = len - 1; i >= 0; i--) {
                if (input.charAt(i) == ' ') {
                    len--;
                } else {
                    break;
                }
            }
            StringBuilder trimmedString = new StringBuilder(input.substring(0, len));
            len = trimmedString.length();
            for (int i = len - 1; i >= 0; i--) {
                if (trimmedString.charAt(i) == '\n') {
                    len--;
                } else {
                    break;
                }
            }
            trimmedString.setLength(len);
            trimmedString.append('\0'); // Null terminate the string
            System.out.println(trimmedString.toString());
        } else {
            System.out.println("Please provide a valid string argument.");
        }
    }
}