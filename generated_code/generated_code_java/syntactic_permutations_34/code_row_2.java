import java.util.*;
class LoginPage {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.println("Enter username");
        String uname = sc.nextLine();
        System.out.println("Enter password");
        String pass = sc.nextLine();
        if (checkLogin(uname, pass)) {
            System.out.println("Logged in successfully");
            redirectToDashboard();
        } else {
            System.out.println("Invalid username or password");
            redirectToLogin();
        }
    }
}