import java.io.*;
import java.util.*;

public class Login {
    public static void main(String[] args) throws IOException {
        Scanner sc = new Scanner(System.in);
        System.out.println("Enter your name :");
        String name = sc.nextLine();
        System.out.println("Enter your password :");
        String password = sc.nextLine();
        if (name.equals("admin") && password.equals("password")) {
            System.out.println("Hello admin ! You are redirected to the admin page.");
        } else {
            System.out.println("Invalid credentials");
        }
    }
}