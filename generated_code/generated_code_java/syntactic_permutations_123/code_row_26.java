import java.util.*;
    public class TrimString{
        public static void main(String[] args) {
            if (args.length != 1) {
                System.out.println("One argument required");
                return;
            }
            String s = args[0];
            for (int i = 0; i < s.length(); i++) {
                char c = s.charAt(i);
                if (!Character.isWhitespace(c)) {
                    System.out.print(c);
                }
            }
        }
    }