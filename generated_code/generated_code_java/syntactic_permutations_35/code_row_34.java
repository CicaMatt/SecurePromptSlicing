import java.util.*;
public class Login {
    public static void main(String[] args) {
        String username = "admin";
        String password = "pass@123";
        if (username.equals("admin") && password.equals("pass@123")) {
            System.out.println("Welcome");
        } else {
            System.out.println("Invalid credentials");
        }
    }
}