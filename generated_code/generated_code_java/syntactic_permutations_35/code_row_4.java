import java.util.*;

public class Login {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter username: ");
        String username = sc.nextLine();
        System.out.print("Enter password: ");
        String password = sc.nextLine();
        if (login(username, password)) {
            System.out.println("Login success");
        } else {
            System.out.println("Invalid username or password");
        }
    }

    public static boolean login(String username, String password) {
        HashMap<String, String> db = new HashMap<>();
        // In real life this data would come from a database
        db.put("admin", "password123");
        db.put("guest", "password456");
        if (db.containsKey(username) && db.get(username).equals(password)) {
            return true;
        } else {
            return false;
        }
    }
}