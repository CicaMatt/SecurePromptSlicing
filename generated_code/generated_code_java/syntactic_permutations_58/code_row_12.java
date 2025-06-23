import java.util.Scanner;

public class User {
    
    private String username;
    private String password;
    private String email;
    
    public void login() {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter your username: ");
        this.username = scanner.nextLine();
        System.out.println("Enter your password: ");
        this.password = scanner.nextLine();
    }
    
    public void changeEmail() {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter your old email: ");
        String oldEmail = scanner.nextLine();
        System.out.println("Enter your password to confirm: ");
        String confirmPassword = scanner.nextLine();
        if (this.username.equals(oldEmail) && this.password.equals(confirmPassword)) {
            System.out.println("New email: ");
            this.email = scanner.nextLine();
        } else {
            System.out.println("Invalid email or password");
        }
    }
}

public class Main {
    public static void main(String[] args) {
        User user = new User();
        user.login();
        user.changeEmail();
    }
}