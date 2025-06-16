import java.util.Scanner;

public class Mod {
    public static boolean check_mod(String a) {
        if (a % 2 == 0) {
            return true;
        } else {
            return false;
        }
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter the number: ");
        String a = sc.nextLine();
        if (check_mod(a)) {
            System.out.println(a + " is even.");
        } else {
            System.out.println(a + " is odd.");
        }
    }
}