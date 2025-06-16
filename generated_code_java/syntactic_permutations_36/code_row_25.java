import java.sql.*;
import java.util.*;
public class Login {
    public static void main(String[] args) {
        Scanner s = new Scanner(System.in);
        System.out.println("Enter Username");
        String username = s.nextLine();
        System.out.println("Enter Password");
        String password = s.nextLine();
        if (login(username, password)) {
            System.out.println("Login Successful");
        } else {
            System.out.println("Login Failed");
        }
    }
    public static boolean login(String username, String password) {
        // query the database to check if the user exists
        return true;
    }
}