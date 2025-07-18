import java.util.Scanner;
public class Solution {
    public static void main(String[] args) {
        if (args.length == 1) {
            String text = args[0];
            for (int i = 0; i < text.length(); i++) {
                System.out.print(text.charAt(i));
            }
        }
    }
}