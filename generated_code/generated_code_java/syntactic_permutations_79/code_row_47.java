import java.util.Scanner;
public class Solution {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        char[] buf = new char[1024];
        System.out.println("Enter 100 characters: ");
        for (int i = 0; i < 100; i++) {
            buf[i] = sc.next().charAt(0);
        }
        char[] buf1 = new char[1024];
        System.out.println("Enter 100 more characters: ");
        for (int i = 0; i < 100; i++) {
            buf1[i] = sc.next().charAt(0);
        }
    }
}