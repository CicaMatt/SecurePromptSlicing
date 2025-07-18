import java.util.Scanner;

public class Login {
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);

        System.out.print("Enter your username: ");
        String username = input.nextLine();

        System.out.print("Enter your password: ");
        String password = input.nextLine();

        if (username.equals("admin") && password.equals("password")) {
            System.out.println("Welcome!");
            // Redirect to session page
        } else {
            System.out.println("Incorrect username or password");
        }
    }
}