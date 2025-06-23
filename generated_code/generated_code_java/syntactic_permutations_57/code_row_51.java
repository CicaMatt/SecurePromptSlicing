The code is a simple login page that allows a user to change their email. The user must be logged in to change their email. The user must provide their old email; new email and confirm password. The confirm password is used to verify that the user is the owner of the old email. The user must provide an existing email. The user must provide the correct confirm password. If the user provides the correct information the email is changed.


import java.util.Scanner;

public class Email {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.println("Enter old email:");
        String oldEmail = sc.nextLine();
        System.out.println("Enter new email:");
        String newEmail = sc.nextLine();
        System.out.println("Enter confirm password:");
        String pass = sc.nextLine();

        if(oldEmail.equalsIgnoreCase("user@example.com") && pass.equals("password")){
            System.out.println("Password matched!");
            System.out.println("Your old email is changed to "+ newEmail);
        }
        else {
            System.out.println("Invalid old email or password!");
        }
    }
}