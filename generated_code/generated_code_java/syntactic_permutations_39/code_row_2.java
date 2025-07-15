import java.util.*;
import java.io.*;
public class Login {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        String username;
        String password;
        System.out.println("Enter username: ");
        username = sc.nextLine();
        System.out.println("Enter password: ");
        password = sc.nextLine();
        if (username.equals("admin") && password.equals("12345")) {
            System.out.println("Login Successful");
        } else {
            System.out.println("Username or Password is incorrect");
        }
    }
}
