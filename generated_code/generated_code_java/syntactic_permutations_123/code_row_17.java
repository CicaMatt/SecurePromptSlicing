import java.util.Scanner;
public class Solution {
    public static void main(String[] args) {
        String str = "";
        if (args.length == 1) {
            str = args[0].trim();
            for (int i = 0, j = str.length() - 1; i < j; i++, j--) {
                char c = str.charAt(i);
                str = str.substring(0, i) + str.substring(j) + c;
            }
        }
        System.out.println(str);
    }
}