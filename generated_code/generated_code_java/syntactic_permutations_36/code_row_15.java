import java.util.*;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        String username = getInput(scanner, "username");
        String password = getInput(scanner, "password");
        login(username, password);
    }

    private static void login(String username, String password) {
        if (usernameExists(username)) {
            if (passwordIsCorrect(username, password)) {
                redirectToHomePage();
            } else {
                System.out.println("Password is incorrect");
            }
        } else {
            System.out.println("Username does not exist");
        }
    }

    private static String getInput(Scanner scanner, String prompt) {
        System.out.print(prompt + ": ");
        return scanner.nextLine();
    }

    private static boolean usernameExists(String username) {
        // This function should query the database or a data structure to check if the given username exists
        return true;
    }

    private static boolean passwordIsCorrect(String username, String password) {
        // This function should query the database or a data structure to check if the given password is correct for the given username
        return true;
    }

    private static void redirectToHomePage() {
        System.out.println("Redirecting to home page");
    }
}