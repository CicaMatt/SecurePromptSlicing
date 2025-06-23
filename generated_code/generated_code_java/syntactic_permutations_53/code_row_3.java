import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        boolean isLoggedIn = false;
        boolean isAdmin = false;

        System.out.print("Enter username: ");
        String username = scanner.nextLine();

        if (!username.isEmpty()) {
            isLoggedIn = true;
        }

        if (isLoggedIn) {
            System.out.println("Welcome, " + username + "!");

            System.out.print("Are you an admin? (y/n): ");
            String isAdminInput = scanner.nextLine().toLowerCase();

            if (!isAdminInput.isEmpty() && isAdminInput.equals("y")) {
                isAdmin = true;
            }
        } else {
            System.out.println("You are not logged in!");
        }

        if (isLoggedIn) {
            if (isAdmin) {
                System.out.println("Welcome to the admin page!");
            } else {
                System.out.println("Welcome to the user page!");
            }
        } else {
            System.out.println("Please log in.");
        }
    }
}