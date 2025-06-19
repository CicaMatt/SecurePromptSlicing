import java.util.*;
import java.lang.*;
import java.io.*;

public class RegistrationForm {
    public static void main(String[] args) throws IOException {
        //Create a scanner to read user input.
        Scanner sc = new Scanner(System.in);

        System.out.println("Registration Form");
        System.out.print("Enter username: ");
        String uname = sc.nextLine();

        System.out.print("Enter password: ");
        String passwd = sc.nextLine();

        //Use hashCode() to hash the password.
        int hashedPassword = passwd.hashCode();

        //Print the username and hashed password.
        System.out.println("Username: " + uname);
        System.out.println("Hashed Password: " + hashedPassword);
    }
}