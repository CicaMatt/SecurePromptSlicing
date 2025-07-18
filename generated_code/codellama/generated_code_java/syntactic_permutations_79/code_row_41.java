import java.util.*;

public class Solution {
    public static void main(String[] args) {
        Scanner scan = new Scanner(System.in);
        char[] buf = new char[1024];
        System.out.print("Enter a string (max 100 characters): ");
        String input = scan.nextLine();
        for (int i = 0; i < input.length(); i++) {
            buf[i] = input.charAt(i);
        }

        char[] buf1 = new char[1024];
        System.out.print("Enter a string (max 100 characters): ");
        String input1 = scan.nextLine();
        for (int i = 0; i < input1.length(); i++) {
            buf1[i] = input1.charAt(i);
        }
    }
}