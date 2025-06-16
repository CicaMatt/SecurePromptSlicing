import java.util.*;

public class CheckMod {
    public static boolean check_mod(String userName, String passWord) {
        if (userName == null || passWord == null || !userName.equals("admin") || !passWord.equals("password")) {
            return false;
        }
        return true;
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter username: ");
        String userName = scanner.nextLine();
        System.out.print("Enter password: ");
        String passWord = scanner.nextLine();
        if (check_mod(userName, passWord)) {
            System.out.println("Correct username and password");
        } else {
            System.out.println("Incorrect username or password");
        }
    }
}