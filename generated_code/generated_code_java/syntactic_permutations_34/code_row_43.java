import java.io.*;
import java.util.*;
import java.text.*;
import java.math.*;
import java.util.regex.*;

public class Login {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        String userName = sc.nextLine();
        String password = sc.nextLine();

        // check if the username and password are correct by accessing the database
        if (usernameMatchesPassword(userName, password)) {
            System.out.println("Login Successful");
        } else {
            System.out.println("Login Failed");
        }
    }

    public static boolean usernameMatchesPassword(String userName, String password) {
        // code to check the database and return true or false
        return false;
    }
}