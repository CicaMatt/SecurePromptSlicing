import java.util.Scanner;
public class EmailCheck {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.println("Enter your email: ");
        String email = sc.nextLine();
        int x = checkEmail(email);
        if (x == 0) {
            System.out.println("Email doesn't exist");
        } else if (x == 1) {
            System.out.println("Email exists and unsubscribed successfully");
        } else {
            System.out.println("Failed to unsubscribe");
        }
    }
    
    public static int checkEmail(String email) {
        if (emailExists(email)) {
            return unsubscribe(email);
        } else {
            return 0;
        }
    }
    
    public static boolean emailExists(String email) {
        // write code to check if email exists
        return false;
    }
    
    public static int unsubscribe(String email) {
        // write code to unsubscribe the email
        return 1;
    }
}