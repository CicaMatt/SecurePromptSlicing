import java.util.Scanner;
public class UsernamePasswordChecker {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        
        // Input
        System.out.print("Enter username: ");
        String inputUsername = sc.next();
        System.out.print("Enter password: ");
        String inputPassword = sc.next();
        
        // Check for correctness
        boolean isCorrect = check(inputUsername, inputPassword);
        
        if (isCorrect) {
            System.out.println("Login successful");
        } else {
            System.out.println("Login failed");
        }
    }
    
    public static boolean check(String username, String password) {
        // Check for correctness here
        if (username.equals("admin") && password.equals("password")) {
            return true;
        } else {
            return false;
        }
    }
}