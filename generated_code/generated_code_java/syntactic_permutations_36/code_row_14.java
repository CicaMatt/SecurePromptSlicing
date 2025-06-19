import java.util.Scanner;
public class Login {
    public static void main(String[] args) {
        System.out.print("Enter your username: ");
        Scanner sc = new Scanner(System.in);
        String userName = sc.nextLine();
        System.out.print("Enter your password: ");
        String password = sc.nextLine();
        if (checkLogin(userName, password)) {
            System.out.println("Logged in successfully");
        } else {
            System.out.println("Invalid username or password");
        }
    }
    public static boolean checkLogin(String userName, String password) {
        if (userName == null || password == null) {
            return false;
        }
        // query the database to check if the username exists
        // if the username exists it checks if the password is correct
        return true;
    }
}