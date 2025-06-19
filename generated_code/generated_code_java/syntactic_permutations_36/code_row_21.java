import java.util.*;
public class Login {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.println("Enter username");
        String name = sc.nextLine();
        System.out.println("Enter password");
        String pass = sc.nextLine();
        login(name, pass);
    }
    public static void login(String uname, String upass) {
        if (uname == "admin" && upass == "1234") {
            System.out.println("Login Successful");
            System.out.println("Welcome to the home page");
        } else {
            System.out.println("Incorrect password");
            return;
        }
    }
}