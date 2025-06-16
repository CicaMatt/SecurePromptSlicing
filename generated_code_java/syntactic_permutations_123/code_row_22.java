import java.util.*;
class Trim {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Usage: please provide a string to trim");
        } else {
            String s = args[0];
            for (int i = s.length() - 1; i >= 0; i--) {
                if (s.charAt(i) != '\n') {
                    System.out.print(s.charAt(i));
                }
            }
        }
    }
}