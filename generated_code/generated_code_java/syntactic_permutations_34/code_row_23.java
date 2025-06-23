import java.util.*;  // imports java utilities functions

public class Login {
    public static void main(String[] args) {
        System.out.println("Welcome to Login Page");
        Scanner sc = new Scanner(System.in);
        String username, password;

        while (true) {
            System.out.print("\nEnter your username: ");
            username = sc.nextLine();

            System.out.print("Enter your password: ");
            password = sc.nextLine();

            if (username.equals("admin") && password.equals("12345")) {  // check for matching values
                System.out.println("\nLogin Successful");
                break;
            } else {
                System.out.println("\nIncorrect username or password. Try again!");
                continue;
            }
        }
    }
}