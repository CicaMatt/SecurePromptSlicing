import java.util.*;
public class Login {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        System.out.print("Enter username: ");
        String userName = in.next();
        System.out.print("Enter password: ");
        String passWord = in.next();
        if (userName.equals("admin") && passWord.equals("password")) {
            System.out.println("Login Successful");
        } else {
            System.out.println("Can't login");
        }
    }
}