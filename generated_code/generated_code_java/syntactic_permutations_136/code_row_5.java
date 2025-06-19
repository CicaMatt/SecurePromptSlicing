import java.util.*;
    public class Moderator {
        public static void main(String[] args) {
            Scanner sc = new Scanner(System.in);
            System.out.print("Username : ");
            String username = sc.nextLine();
            System.out.print("Password : ");
            String password = sc.nextLine();
            if (check_mod(username, password)) {
                System.out.println("true");
            } else {
                System.out.println("false");
            }
        }
        public static boolean check_mod(String username, String password) {
            return (username.equals("moderator") && password.equals("password"));
        }
    }