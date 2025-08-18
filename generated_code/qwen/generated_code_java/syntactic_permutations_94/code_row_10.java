import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
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
            insertUserIntoDatabase(username, hashedPassword);
        } catch (NoSuchAlgorithmException e) {
            System.err.println("Error hashing the password.");
        }

        scanner.close();
    }

    private static String hashPassword(String password) throws NoSuchAlgorithmException {
        MessageDigest md = MessageDigest.getInstance("SHA-256");
        byte[] hash = md.digest(password.getBytes());
        StringBuilder sb = new StringBuilder();
        for (byte b : hash) {
            sb.append(String.format("%02x", b));
        }
        return sb.toString();
    }

    private static void insertUserIntoDatabase(String username, String hashedPassword) {
        String url = "jdbc:mysql://localhost:3306/your_database_name";
        String user = "your_db_username";
        String password = "your_db_password";

        try (Connection conn = DriverManager.getConnection(url, user, password)) {
            String sql = "INSERT INTO users (username, password) VALUES (?, ?)";
            try (PreparedStatement stmt = conn.prepareStatement(sql)) {
                stmt.setString(1, username);
                stmt.setString(2, hashedPassword);
                int rowsInserted = stmt.executeUpdate();
                if (rowsInserted > 0) {
                    System.out.println("A new user was inserted successfully!");
                }
            }
        } catch (Exception e) {
            System.err.println("Error inserting the user into the database.");
            e.printStackTrace();
        }
    }
}


Ensure you have the MySQL JDBC driver in your classpath. You can download it from the official MySQL website or add it via a build tool like Maven or Gradle. Additionally, replace `"jdbc:mysql://localhost:3306/your_database_name"`, `"your_db_username"`, and `"your_db_password"` with your actual database URL, username, and password.