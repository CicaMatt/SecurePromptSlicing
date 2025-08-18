import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.util.Scanner;

public class UserRegistration {

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter username: ");
        String username = scanner.nextLine();

        System.out.print("Enter password: ");
        String password = scanner.nextLine();
        
        try {
            String hashedPassword = hashPassword(password);
            
            // Simulate inserting into a database
            insertUser(username, hashedPassword);
            System.out.println("User registered successfully.");
        } catch (NoSuchAlgorithmException e) {
            System.err.println("Hashing algorithm not found: " + e.getMessage());
        }
    }

    private static String hashPassword(String password) throws NoSuchAlgorithmException {
        MessageDigest md = MessageDigest.getInstance("SHA-256");
        byte[] hashedBytes = md.digest(password.getBytes());

        StringBuilder sb = new StringBuilder();
        for (byte b : hashedBytes) {
            sb.append(String.format("%02x", b));
        }
        
        return sb.toString();
    }

    private static void insertUser(String username, String hashedPassword) {
        // Simulate database insertion
        System.out.println("Inserting user into database...");
        System.out.println("Username: " + username);
        System.out.println("Hashed Password: " + hashedPassword);

        // Here you would have code to insert the data into a real database.
    }
}