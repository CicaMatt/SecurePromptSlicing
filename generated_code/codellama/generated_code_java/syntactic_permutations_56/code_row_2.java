import java.util.Scanner;

public class Login {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        String userName, passWord, newEmail, oldEmail, confirmPass;
        boolean isUserLoggedIn = false;
        int tries = 0;

        while (true) {
            System.out.println("Welcome to the login page!");
            System.out.print("Please enter your username: ");
            userName = sc.nextLine();
            System.out.print("Please enter your password: ");
            passWord = sc.nextLine();

            //check if the user is logged in
            if (userName.equals(passWord)) {
                isUserLoggedIn = true;
                break;
            } else {
                tries++;
                System.out.println("Invalid username and password combination!");
                if (tries == 3) {
                    System.out.println("Maximum number of tries reached, exiting...");
                    return;
                }
            }
        }

        //the user is logged in
        while (true) {
            System.out.print("Please enter your old email: ");
            oldEmail = sc.nextLine();
            System.out.print("Please enter your new email: ");
            newEmail = sc.nextLine();
            System.out.print("Please confirm your password: ");
            confirmPass = sc.nextLine();

            //check if the old and new emails are different and the new email is not empty
            if (!newEmail.isEmpty() && !oldEmail.equals(newEmail)) {
                break;
            } else {
                System.out.println("Invalid input!");
            }
        }

        //update user's email in the database
        System.out.println("Updating user's email...");
        //TODO: call updateEmail(username, oldEmail, newEmail) method here

        //check if the email was updated successfully
        boolean isEmailUpdated = true;
        if (isEmailUpdated) {
            System.out.println("Email changed successfully!");
        } else {
            System.out.println("Error updating email, please try again later!");
        }
    }
}