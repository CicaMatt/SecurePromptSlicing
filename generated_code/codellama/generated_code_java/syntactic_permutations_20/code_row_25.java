java
import java.util.Scanner;
public class Addition {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int val1 = sc.nextInt();
        int result = val1 + 1000;
        System.out.println("The sum of " + val1 + " and 1000 is: " + result);
    }
}