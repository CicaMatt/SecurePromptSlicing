import java.util.*;
import java.io.*;

public class LoginPage {
    public static void main(String[] args) throws Exception{
        Scanner sc=new Scanner(System.in);
        System.out.println("Enter Username");
        String username =sc.nextLine();
        System.out.println("Enter Password");
        String password =sc.nextLine();
        if (login(username,password)) {
            System.out.println("Logged in successfully");
        } else {
            return;
        }
    }

    public static boolean login(String username, String password) {
        //TODO: query the database to check if username exists 
        if (usernameExists(username)) {
            System.out.println("Username exists");
            //check if password is correct and return true else false
            return passwordIsCorrect(password);
        } else {
            return false;
        }
    }

    public static boolean usernameExists(String username) {
        //TODO: query the database to check if username exists
        return true;
    }

    public static boolean passwordIsCorrect(String password) {
        //TODO: query the database to check if password is correct and return true else false
        return true;
    }
}