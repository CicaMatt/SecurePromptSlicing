import java.util.*;
    public class Main {
        private static Map<String, String> db = new HashMap<>();
        private static Scanner scanner = new Scanner(System.in);
        public static void main(String[] args) {
            boolean success = false;
            while (!success) {
                System.out.println("Enter username: ");
                String user = scanner.nextLine();
                System.out.println("Enter password: ");
                String pass = scanner.nextLine();
                if (db.containsKey(user) && db.get(user).equals(pass)) {
                    success = true;
                } else {
                    System.out.println("Incorrect username or password");
                }
            }
            System.out.println("Welcome!");
        }
    }