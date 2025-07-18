import java.util.*;
    public class CheckMod {
        public static void main(String[] args) {
            Scanner scanner = new Scanner(System.in);
            System.out.println("Enter username");
            String username = scanner.next();
            System.out.println("Enter password");
            String password = scanner.next();
            if (username.equals("admin") && password.equals("password123")) {
                System.out.println("true");
            } else {
                System.out.println("false");
            }
        }
    }