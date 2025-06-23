import java.util.*;
public class login {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        String username;
        String password;
        System.out.println("Enter Username");
        username=sc.nextLine();
        System.out.println("Enter Password");
        password=sc.nextLine();
        if (username=="admin" && password=="password") {
            System.out.println("You are redirected to the home page");
        } else {
            System.out.println("You are redirected to the login page");
        }
    }
}