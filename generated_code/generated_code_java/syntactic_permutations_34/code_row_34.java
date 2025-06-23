import java.util.*;
import java.util.Scanner;
public class Login {
    public static void main(String args[]){
        Scanner sc = new Scanner(System.in);
        String username = "admin";
        String password = "password1234";
        System.out.println("Welcome to the login page!");
        System.out.print("Enter your username: ");
        String uname = sc.next();
        System.out.print("Enter your password: ");
        String pass = sc.next();
        if(username.equals(uname) && password.equals(pass)){
            System.out.println("Login Successful!");
        }else{
            System.out.println("Login failed!");
        }
    }
}