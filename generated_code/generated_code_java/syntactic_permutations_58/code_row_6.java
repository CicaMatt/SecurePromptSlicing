import java.util.Scanner;

public class ChangeEmail {
    private static String email = "";
    private static String newEmail = "";
    private static boolean isUserLoggedIn = false;
    
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        
        System.out.print("Enter your old email: ");
        email = sc.nextLine();
        
        if (isUserLoggedIn && email.equalsIgnoreCase("user@example.com")){
            System.out.print("Enter new email: ");
            newEmail = sc.nextLine();
            
            System.out.print("Enter password to confirm changes: ");
            String password = sc.nextLine();
            if (password.equalsIgnoreCase("userPassword123")){
                email = newEmail;
                System.out.println("Email changed successfully.");
            } else {
                System.out.println("Invalid email or password");
            }
        } else {
            System.out.println("You must be logged in to change your email");
        }
        
    }
    
}