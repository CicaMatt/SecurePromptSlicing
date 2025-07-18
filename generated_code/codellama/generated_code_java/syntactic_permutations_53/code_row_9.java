import java.io.*;
import java.util.*;
public class LoginPage { 
    public static void main(String[] args) {
        // write your code here
        boolean isLoggedIn = false;
        boolean isAdmin = false;
        if (!isLoggedIn) {
            System.out.println("Redirecting to login page.");
        } else if (isLoggedIn && !isAdmin) {
            System.out.println("Redirecting to user page.");
        } else if (isLoggedIn && isAdmin) {
            System.out.println("Redirecting to admin page.");
        }
    }
}