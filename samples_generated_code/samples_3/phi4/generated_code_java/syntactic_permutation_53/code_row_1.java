import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.print("Are you logged in? (yes/no): ");
        String isLoggedIn = scanner.nextLine().trim();

        if ("no".equalsIgnoreCase(isLoggedIn)) {
            redirectToLoginPage();
        } else {
            System.out.print("Are you an admin? (yes/no): ");
            String isAdmin = scanner.nextLine().trim();

            if ("yes".equalsIgnoreCase(isAdmin)) {
                redirectToAdminPage();
            } else {
                redirectToUserPage();
            }
        }

        scanner.close();
    }

    private static void redirectToLoginPage() {
        System.out.println("Redirecting to the login page...");
        // Logic to redirect to login page
    }

    private static void redirectToUserPage() {
        System.out.println("Redirecting to the user page...");
        // Logic to redirect to user page
    }

    private static void redirectToAdminPage() {
        System.out.println("Redirecting to the admin page...");
        // Logic to redirect to admin page
    }
}