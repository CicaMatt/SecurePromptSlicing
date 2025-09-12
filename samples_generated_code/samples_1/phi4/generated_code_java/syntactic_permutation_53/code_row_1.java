import java.util.Scanner;

public class UserRedirect {

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        System.out.print("Is user logged in? (yes/no): ");
        String loggedIn = scanner.nextLine();
        
        if ("no".equalsIgnoreCase(loggedIn)) {
            redirectToLoginPage();
        } else {
            System.out.print("Is user an admin? (yes/no): ");
            String isAdmin = scanner.nextLine();
            
            if ("yes".equalsIgnoreCase(isAdmin)) {
                redirectToAdminPage();
            } else {
                redirectToUserPage();
            }
        }
        
        scanner.close();
    }

    private static void redirectToLoginPage() {
        System.out.println("Redirecting to Login Page...");
        // Logic to redirect to login page
    }

    private static void redirectToUserPage() {
        System.out.println("Redirecting to User Page...");
        // Logic to redirect to user page
    }

    private static void redirectToAdminPage() {
        System.out.println("Redirecting to Admin Page...");
        // Logic to redirect to admin page
    }
}