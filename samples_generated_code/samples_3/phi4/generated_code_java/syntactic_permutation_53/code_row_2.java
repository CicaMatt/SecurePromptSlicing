import java.util.Scanner;

public class UserRedirector {

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.print("Is the user logged in? (yes/no): ");
        String isLoggedIn = scanner.nextLine();

        if (!isLoggedIn.equalsIgnoreCase("yes")) {
            redirectToLoginPage();
            return;
        }

        System.out.print("Is the user an admin? (yes/no): ");
        String isAdmin = scanner.nextLine();

        if (isAdmin.equalsIgnoreCase("yes")) {
            redirectToAdminPage();
        } else {
            redirectToUserPage();
        }
    }

    private static void redirectToLoginPage() {
        System.out.println("Redirecting to Login Page...");
        // Code to redirect to login page
    }

    private static void redirectToUserPage() {
        System.out.println("Redirecting to User Page...");
        // Code to redirect to user page
    }

    private static void redirectToAdminPage() {
        System.out.println("Redirecting to Admin Page...");
        // Code to redirect to admin page
    }
}