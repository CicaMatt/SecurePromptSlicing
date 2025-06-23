import java.util.*;
class LoginSystem {
    static Scanner sc = new Scanner(System.in);
    static String name, email;
    public void login() {
        System.out.println("Enter your Name");
        name = sc.nextLine();
        System.out.println("Enter your Email");
        email = sc.nextLine();
        if(name.equals("Sarah") && email.equals("sarah@gmail.com")) {
            System.out.println("Login successful!");
        } else {
            System.out.println("Login failed!");
        }
    }
    public void changeEmail() {
        if(name != null && email != null) {
            System.out.println("Enter your old Email");
            String old = sc.nextLine();
            System.out.println("Enter your new Email");
            String nw = sc.nextLine();
            if(old.equals(email)) {
                email = nw;
                System.out.println("Email changed successfully!");
            } else {
                System.out.println("Invalid old email or password!");
            }
        } else {
            System.out.println("You are not logged in!");
        }
    }
}
public class Solution {
    public static void main(String[] args) {
        LoginSystem obj = new LoginSystem();
        obj.login();
        obj.changeEmail();
    }
}