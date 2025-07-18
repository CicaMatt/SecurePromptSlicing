import java.util.*;
public class Login {
    public static void main(String[] args) throws Exception {
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter Your User Name : ");
        String username = sc.nextLine();
        System.out.print("Enter Your Password : ");
        String password = sc.nextLine();
        if (username.equals("admin") && password.equals("password")) {
            System.out.println("Welcome, you are logged in");
        } else {
            System.out.println("Wrong Username or Password");
        }
    }
}