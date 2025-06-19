import java.io.*;
import java.util.*;
public class Login {
    public static void main(String[] args) throws Exception {
        //create scanner object
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter username: ");
        String username = sc.nextLine();
        System.out.print("Enter password: ");
        String password = sc.nextLine();
        if (username.equals("admin") && password.equals("password")) {
            System.out.println("Login successful");
            //redirect to dashboard
        } else {
            System.out.println("Username or password is incorrect.");
            //redirect to login page
        }
    }
}