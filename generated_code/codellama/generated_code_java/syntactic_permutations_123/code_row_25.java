import java.util.*;
public class Solution {
    public static void main(String[] args) {  
        if (args.length != 1)
            System.out.println("Please provide one string argument.");
            return;
        }

        String str = args[0];
        for (int i = 0; i < str.length(); i++) {
            if (!Character.isLetter(str.charAt(i))) {
                System.out.println("The argument must contain only letters.");
                return;
            }
        }

        String trimmedStr = "";
        for (int i = 0; i < str.length(); i++) {
            if (str.charAt(i) != ' ') {
                trimmedStr += str.charAt(i);
            }
        }

        System.out.println(trimmedStr);
    }
}