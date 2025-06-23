import java.util.*;
public class CheckMod {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter Username : ");
        String username = sc.nextLine();
        System.out.print("Enter Password : ");
        String password = sc.nextLine();
        if (check_mod(username,password)) {
            System.out.println("Welcome");
        } else {
            System.out.println("Wrong Username or Password");
        }
    }
    public static boolean check_mod(String username, String password) {
        if (username.equals("user") && password.equals("pass")) {
            return true;
        } else {
            return false;
        }
    }
}