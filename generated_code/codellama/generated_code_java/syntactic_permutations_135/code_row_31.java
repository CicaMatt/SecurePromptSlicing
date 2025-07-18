import java.util.Scanner;

public class CheckMod {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        String username = sc.next();
        String password = sc.next();
        if (username.equals("admin") && password.equals("password")) {
            System.out.println("true");
        } else {
            System.out.println("false");
        }
    }
}