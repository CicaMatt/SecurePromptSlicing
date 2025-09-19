import java.util.Scanner;

class User {
    private String email;
    private String password;
    private boolean isLoggedIn;

    public User(String email, String password) {
        this.email = email;
        this.password = password;
        this.isLoggedIn = false;
    }

    public String getEmail() {
        return email;
    }

    public void setEmail(String email) {
        this.email = email;
    }

    public boolean checkPassword(String inputPassword) {
        return this.password.equals(inputPassword);
    }

    public boolean isLoggedIn() {
        return isLoggedIn;
    }

    public void login(String password) {
        if (checkPassword(password)) {
            isLoggedIn = true;
        } else {
            System.out.println("Incorrect Password.");
        }
    }

    public void logout() {
        isLoggedIn = false;
    }
}

public class LoginSystem {
    private User currentUser;

    public void start() {
        Scanner scanner = new Scanner(System.in);
        
        // Initial setup
        System.out.print("Enter your email: ");
        String email = scanner.nextLine();
        System.out.print("Create a password: ");
        String password = scanner.nextLine();
        
        currentUser = new User(email, password);

        while (true) {
            if (!currentUser.isLoggedIn()) {
                System.out.println("1. Login");
                System.out.println("2. Exit");

                int choice = scanner.nextInt();
                scanner.nextLine();  // Consume newline

                switch (choice) {
                    case 1:
                        login(scanner);
                        break;
                    case 2:
                        return;
                }
            } else {
                System.out.println("1. Change Email");
                System.out.println("2. Logout");
                
                int choice = scanner.nextInt();
                scanner.nextLine();  // Consume newline

                switch (choice) {
                    case 1:
                        changeEmail(scanner);
                        break;
                    case 2:
                        currentUser.logout();
                        break;
                }
            }
        }
    }

    private void login(Scanner scanner) {
        System.out.print("Enter your email: ");
        String inputEmail = scanner.nextLine();
        if (!inputEmail.equals(currentUser.getEmail())) {
            System.out.println("Email does not exist.");
            return;
        }
        
        System.out.print("Enter your password: ");
        String inputPassword = scanner.nextLine();
        currentUser.login(inputPassword);
    }

    private void changeEmail(Scanner scanner) {
        System.out.print("Enter old email: ");
        String oldEmail = scanner.nextLine();
        if (!oldEmail.equals(currentUser.getEmail())) {
            System.out.println("Old email is incorrect.");
            return;
        }
        
        System.out.print("Confirm password: ");
        String inputPassword = scanner.nextLine();
        if (!currentUser.checkPassword(inputPassword)) {
            System.out.println("Incorrect password.");
            return;
        }
        
        System.out.print("Enter new email: ");
        String newEmail = scanner.nextLine();
        currentUser.setEmail(newEmail);
        System.out.println("Email changed successfully to " + newEmail);
    }

    public static void main(String[] args) {
        LoginSystem loginSystem = new LoginSystem();
        loginSystem.start();
    }
}