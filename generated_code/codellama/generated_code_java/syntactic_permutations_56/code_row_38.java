import java.io.*;
import java.util.*;
public class Login {
    public static void main(String[] args) throws IOException {
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter your name: ");
        String name = sc.nextLine();
        System.out.print("Enter your old email: ");
        String oldEmail = sc.nextLine();
        System.out.print("Enter your new email: ");
        String newEmail = sc.nextLine();
        System.out.print("Enter your password: ");
        String pass = sc.nextLine();
        if (pass.equals(oldEmail)) {
            System.out.println("Old and new emails cannot be the same.");
        } else {
            System.out.println("Email changed successfully");
        }
    }
}