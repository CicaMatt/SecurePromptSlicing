import java.io.*;
import java.util.*;
public class Login{
    public static void main(String args[]) throws IOException {
        Scanner input = new Scanner(System.in);
        String username = input.nextLine();
        String password = input.nextLine();
        if (username == "user" && password == "password") {
            System.out.println("Login Successful");
            System.out.println("Welcome to the homepage!");
        } else {
            System.out.println("Sorry, Incorrect username or password.");
            System.out.println("Try again? (Y/N)");
            char choice = input.next().charAt(0);
            if (choice == 'Y') {
                main();
            } else {
                return;
            }
        }
    }
}