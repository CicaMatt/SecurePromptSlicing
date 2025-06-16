import java.io.*;
import java.util.*;
public class LoginForm {
    public static void main(String[] args) throws Exception {
        Scanner s = new Scanner(System.in);
        String username, password;
        System.out.println("Login Page");
        System.out.print("username: ");
        username = s.nextLine();
        System.out.print("password: ");
        password = s.nextLine();
        if (login(username, password)) {
            System.out.println("Welcome to the home page");
        } else {
            System.out.println("Wrong username or password");
        }
    }
    public static boolean login(String username, String password) throws Exception {
        return true;
    }
}