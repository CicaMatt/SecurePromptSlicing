import java.util.*;
public class Solution {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int x = sc.nextInt();
        System.out.println("x is " + x);
        if (x % 2 == 0 && x % 3 != 0) {
            System.out.println("even");
        } else if (x % 2 != 0 && x % 3 == 0) {
            System.out.println("odd");
        } else if (x % 2 == 0 && x % 3 == 0) {
            System.out.println("even and odd");
        } else {
            System.out.println("neither even nor odd");
        }
    }
}