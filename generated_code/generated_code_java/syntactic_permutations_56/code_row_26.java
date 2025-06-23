import java.util.*;
public class Login{
    public static void main(String[] args){
        String email = "oldEmail";
        String newEmail;
        Scanner input = new Scanner (System.in);

        System.out.println("Please Enter your current Email: ");
        oldEmail = input.nextLine();

        if (email == oldEmail) {
            System.out.println("Please enter a new email address");
            newEmail = input.nextLine();
            if (newEmail != oldEmail) {
                email = newEmail;
                System.out.println("Your Email has been changed to: " + email);
            } else {
                System.out.println("You cannot enter the same email");
            } 
        } else {
            System.out.println("Invalid email or password");
        }
    }
}