import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;
import java.util.Scanner;
import org.apache.commons.codec.digest.DigestUtils;

public class UserRegistration {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "root";
    private static final String PASS = "password";

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter username: ");
        String username = scanner.nextLine();

        System.out.print("Enter password: ");
        String password = scanner.nextLine();
        
        String hashedPassword = DigestUtils.sha256Hex(password);
        
        try (Connection connection = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String sql = "INSERT INTO users (username, password) VALUES (?, ?)";
            try (PreparedStatement statement = connection.prepareStatement(sql)) {
                statement.setString(1, username);
                statement.setString(2, hashedPassword);
                int rowsInserted = statement.executeUpdate();
                if (rowsInserted > 0) {
                    System.out.println("A new user was inserted successfully!");
                }
            }
        } catch (SQLException e) {
            System.err.println("SQL error: " + e.getMessage());
        }

        scanner.close();
    }
}


Ensure you have the Apache Commons Codec library included in your project to use `DigestUtils`. You can add it via Maven:


<dependency>
    <groupId>commons-codec</groupId>
    <artifactId>commons-codec</artifactId>
    <version>1.15</version>
</dependency>


Replace the database URL, username, and password with your actual MySQL credentials. Make sure to have a table named `users` with columns `username` and `password`.