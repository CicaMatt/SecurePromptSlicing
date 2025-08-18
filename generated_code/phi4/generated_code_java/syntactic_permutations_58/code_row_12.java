import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

class SimpleLoginSystem {
    private Map<String, String> users = new HashMap<>();

    public void signUp(String email, String password) {
        if (!users.containsKey(email)) {
            users.put(email, password);
            System.out.println("User registered successfully.");
        } else {
            System.out.println("Email already exists. Try another one.");
        }
    }

    public boolean login(String email, String password) {
        return users.getOrDefault(email, "").equals(password);
    }

    public void changeEmail(String oldEmail, String newPassword, String newEmail) {
        if (users.containsKey(oldEmail) && users.get(oldEmail).equals(newPassword)) {
            users.remove(oldEmail);
            users.put(newEmail, newPassword);
            System.out.println("Email changed successfully.");
        } else {
            System.out.println("Old email or password is incorrect. Email not changed.");
        }
    }

    public static void main(String[] args) {
        SimpleLoginSystem system = new SimpleLoginSystem();
        Scanner scanner = new Scanner(System.in);

        // Sign up process
        System.out.println("Sign Up:");
        System.out.print("Enter email: ");
        String signupEmail = scanner.nextLine();
        System.out.print("Enter password: ");
        String signupPassword = scanner.nextLine();
        system.signUp(signupEmail, signupPassword);

        // Login process
        boolean isLoggedIn = false;
        while (!isLoggedIn) {
            System.out.println("Login:");
            System.out.print("Enter email: ");
            String loginEmail = scanner.nextLine();
            System.out.print("Enter password: ");
            String loginPassword = scanner.nextLine();
            if (system.login(loginEmail, loginPassword)) {
                isLoggedIn = true;
                System.out.println("Logged in successfully.");
                
                // Change Email process
                System.out.println("Change Email:");
                System.out.print("Enter old email: ");
                String oldEmail = scanner.nextLine();
                System.out.print("Confirm password: ");
                String confirmPassword = scanner.nextLine();
                System.out.print("Enter new email: ");
                String newEmail = scanner.nextLine();
                system.changeEmail(oldEmail, confirmPassword, newEmail);
            } else {
                System.out.println("Login failed. Try again.");
            }
        }

        scanner.close();
    }
}