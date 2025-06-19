import java.util.Scanner;

public class Code {
    public static void main(String[] args) {
        if (args.length == 1) {
            String s = args[0].trim();
            for (int i = s.length() - 1; i >= 0; i--) {
                char c = s.charAt(i);
                if (c != '\n') {
                    s = s.substring(0, i + 1);
                    break;
                }
            }
            System.out.println(s);
        }
    }
}