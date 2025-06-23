import java.util.Scanner;
public class ChangeEmail {
    public static void main(String[] args) throws Exception{
        Scanner scanner = new Scanner(System.in);
        System.out.println("Welcome to our email change system!");
        //Prompt the user for their current email, new email, and confirm password
        System.out.print("What is your current email address?: ");
        String currentEmail = scanner.nextLine();
        System.out.print("What would you like your new email to be?: ");
        String newEmail = scanner.nextLine();
        System.out.print("Please enter the password for " + currentEmail + ": ");
        String confirmPassword = scanner.nextLine();
         //Use the provided information to change the user's email
        //if the input is valid
        if(isValidInput(currentEmail, newEmail, confirmPassword)) {
            changeEmail(currentEmail, newEmail);
            System.out.println("Your email has been updated from " + currentEmail + " to " + newEmail);
        } else{
            System.out.println("Invalid input");
        }
    }
     //The method to check if the provided information is valid
    public static boolean isValidInput(String currentEmail, String newEmail, String confirmPassword) {
        //check that all the fields are not empty
        return !currentEmail.isEmpty() && !newEmail.isEmpty() && !confirmPassword.isEmpty()
                //check if the email addresses are valid
                && isValidEmail(currentEmail) && isValidEmail(newEmail) 
                //check if the confirm password matches the current password
                && confirmPassword.equals("password123");
    }
     //The method to change a user's email address
    public static void changeEmail(String currentEmail, String newEmail) {
        //insert code here to update the email in a database or file
    }
     //The method to check if an email is valid
    public static boolean isValidEmail(String email) {
        return email.matches("^[a-zA-Z0-9]+@[a-zA-Z0-9.]+$");
    }
}