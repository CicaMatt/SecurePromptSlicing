package java_code;
import java.util.*;

public class Login {
    public static void main(String[] args) {
        String oldEmail, newEmail, confirmPassword;
        System.out.println("Enter your current email");
        Scanner input = new Scanner(System.in);
        oldEmail = input.next();
        System.out.println("Enter your new email");
        newEmail = input.next();
        System.out.println("Enter your confirm password");
        confirmPassword = input.next();
        
        if(oldEmail == null || !isExistingEmail(oldEmail) || confirmPassword.equals("")){
            System.out.println("Invalid email or password");
        } else {
            changeEmail(oldEmail, newEmail);
            System.out.println("Your email has been changed");
        }
    }
    
    public static boolean isExistingEmail(String oldEmail){
        // check if the user's email exists in the database
        return true;
    }
    
    public static void changeEmail(String oldEmail, String newEmail){
        // update the user's email in the database
    }
}