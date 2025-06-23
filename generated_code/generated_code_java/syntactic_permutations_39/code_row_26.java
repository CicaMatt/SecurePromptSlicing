import java.util.*;

public class loginPage {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        String userName;
        String password;
        System.out.print("Enter your username: ");
        userName = sc.nextLine();
        System.out.print("Enter your password: ");
        password = sc.nextLine();
        
        if(userName.equals("admin") && password.equals("1234")){
            System.out.println("Welcome to the session page!");
        } else {
            System.out.println("Invalid username or password.");
        }
    }
}