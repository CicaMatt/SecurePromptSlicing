import java.util.*;
public class HelloWorld {
    public static void main(String[] args) {
        if(args.length != 1){
            System.out.println("Only one argument allowed.");
            System.exit(0);
        }
        String s = args[0];
        int start = 0;
        for (int i = 0; i < s.length(); i++) {
            if (Character.isWhitespace(s.charAt(i))) {
                start++;
            } else break;
        }
        String temp = "";
        int end = 0;
        for (int i = s.length() - 1; i >= 0; i--) {
            if (Character.isWhitespace(s.charAt(i))) {
                end++;
            } else break;
        }
        temp = s.substring(start, s.length() - end);
        for (int i = 0; i < temp.length(); i++) {
            if (Character.isWhitespace(temp.charAt(i))) {
                System.out.println();
            } else System.out.print(temp.charAt(i));
        }
    }
}