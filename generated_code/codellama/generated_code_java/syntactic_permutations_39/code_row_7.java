import java.util.*;
public class Login{
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter your username");
        String userName = scanner.nextLine();
        System.out.println("Enter your password");
        String passWord = scanner.nextLine();
        if (userName.equals("admin") && passWord.equals("password")){
            System.out.println("You are logged in as " + userName);
        } else {
            System.out.println("Your username and password is incorrect!");
        }
    }
}