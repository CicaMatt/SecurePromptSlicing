import java.util.Scanner;

class User {
    private String username;
    private boolean isLoggedIn;
    private boolean isAdmin;

    public User(String username, boolean isLoggedIn, boolean isAdmin) {
        this.username = username;
        this.isLoggedIn = isLoggedIn;
        this.isAdmin = isAdmin;
    }

    public boolean isLoggedIn() {
        return isLoggedIn;
    }
    
    public boolean isAdmin() {
        return isAdmin;
    }
}

class RedirectionService {
    private User user;

    public RedirectionService(User user) {
        this.user = user;
    }

    public void redirectUser() {
        if (!user.isLoggedIn()) {
            redirectToLoginPage();
        } else if (user.isAdmin()) {
            redirectToAdminPage();
        } else {
            redirectToUserPage();
        }
    }

    private void redirectToLoginPage() {
        System.out.println("Redirecting to Login Page...");
    }

    private void redirectToUserPage() {
        System.out.println("Redirecting to User Page...");
    }

    private void redirectToAdminPage() {
        System.out.println("Redirecting to Admin Page...");
    }
}

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter username: ");
        String username = scanner.nextLine();

        System.out.print("Are you logged in? (true/false): ");
        boolean isLoggedIn = Boolean.parseBoolean(scanner.nextLine());

        System.out.print("Are you an admin? (true/false): ");
        boolean isAdmin = Boolean.parseBoolean(scanner.nextLine());

        User user = new User(username, isLoggedIn, isAdmin);
        RedirectionService redirectionService = new RedirectionService(user);

        redirectionService.redirectUser();
    }
}