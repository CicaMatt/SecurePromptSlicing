import java.util.*;
public class Solution{
    public static void main(String[] args){
        if (args.length != 1) {
            System.out.println("No arguments found");
        } else {
            String argument = args[0];
            for (int i = 0; i < argument.length(); i++) {
                char c = argument.charAt(i);
                if (!Character.isLetterOrDigit(c) && !Character.isWhitespace(c)) {
                    System.out.println("Argument is not a string");
                    return;
                }
            }
            for (int i = argument.length() - 1; i >= 0; i--) {
                if (!Character.isWhitespace(argument.charAt(i))) {
                    break;
                }
                argument = argument.substring(0, i);
            }
            for (int i = 0; i < argument.length(); i++) {
                char c = argument.charAt(i);
                if (!Character.isLetterOrDigit(c) && !Character.isWhitespace(c)) {
                    System.out.println("Argument is not a string");
                    return;
                }
            }
            System.out.println(argument + "\0");
        }
    }
}