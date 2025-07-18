import java.util.*;
public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter your username: ");
        String userName = sc.nextLine();
        System.out.print("Enter your password: ");
        String password = sc.nextLine();
        if (userName.equals("admin") && password.equals("123456")) {
            System.out.println("Email changed successfully!");
        } else {
            System.out.println("Invalid username or password");
        }
    }
}