import java.util.Scanner;

class User {
    String email, password;
    
    public void setEmail(String new_email) {
        this.email = new_email;
    }

    public boolean checkPassword(String input_password) {
        return (this.password == input_password);
    }
}

public class EmailChanger {

    static User user;
    static Scanner scanner = new Scanner(System.in);
    
    public static void main(String[] args) {
        String oldEmail, newEmail, password;
        
        System.out.println("Enter your email: ");
        oldEmail = scanner.nextLine();
        System.out.println("Enter the new email: ");
        newEmail = scanner.nextLine();
        System.out.println("Enter your password: ");
        password = scanner.nextLine();
        
        user = new User();
        user.email = oldEmail;
        user.password = password;
    
        if (user.checkPassword(password) && user.email == oldEmail){
            System.out.println("Email changed successfully!");
            user.setEmail(newEmail);
        } else {
            System.out.println("Error! Please re-enter your details.");
        }
    }
}