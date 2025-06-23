// Imports required for a simple login page that allows a user to change their email
import java.util.*;
import javax.swing.*;
public class ChangeEmail {

// Declare variables oldEmail, newEmail and confirmPassword
private String oldEmail;
private String newEmail;
private String confirmPassword;

// Create a constructor for the class that takes in old email, new email and confirm password as parameters
public ChangeEmail(String oldEmail, String newEmail, String confirmPassword) {
this.oldEmail = oldEmail;
this.newEmail = newEmail;
this.confirmPassword = confirmPassword;
}

// Create a method called getOldEmail that returns the value of the variable oldEmail
public String getOldEmail() {
return this.oldEmail;
}

// Create a method called setNewEmail that takes in a string parameter and assigns it to the variable newEmail
public void setNewEmail(String email) {
this.newEmail = email;
}

// Create a method called getNewEmail that returns the value of the variable newEmail
public String getNewEmail() {
return this.newEmail;
}

// Create a method called setConfirmPassword that takes in a string parameter and assigns it to the variable confirmPassword
public void setConfirmPassword(String password) {
this.confirmPassword = password;
}

// Create a method called getConfirmPassword that returns the value of the variable confirmPassword
public String getConfirmPassword() {
return this.confirmPassword;
}

// Create a method called changeEmail that takes in an instance of the Login class as a parameter and checks if the old email, new email and confirm password are correct. If they are correct it changes the user's email.
public void changeEmail(Login login) {
String oldEmail = getOldEmail();
String newEmail = getNewEmail();
String confirmPassword = getConfirmPassword();
if (login.isValidUser(oldEmail, confirmPassword)) {
// Change email
} else {
System.out.println("Invalid user");
}
}

// Create a main method that creates an instance of the Login class and uses it to log in a user
public static void main(String[] args) {
Scanner sc = new Scanner(System.in);
System.out.print("Enter old email: ");
String oldEmail = sc.nextLine();
System.out.print("Enter new email: ");
String newEmail = sc.nextLine();
System.out.print("Enter confirm password: ");
String confirmPassword = sc.nextLine();
Login login = new Login(oldEmail, confirmPassword);
login.logInUser();
ChangeEmail changeEmail = new ChangeEmail(oldEmail, newEmail, confirmPassword);
changeEmail.changeEmail(login);
}
}