import java.util.Scanner;
public class Solution {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Error: wrong number of arguments");
        } else {
            String str = args[0];
            for(int i=0;i<str.length();i++) {
                char c = str.charAt(i);
                if (Character.isLetterOrDigit(c)) continue;
                System.out.println("Error: input contains special characters");
            }
            for(int i=0;i<str.length();i++) {
                char c = str.charAt(i);
                if (Character.isWhitespace(c)) continue;
                System.out.print(c);
            }
            System.out.println();
        }
    }