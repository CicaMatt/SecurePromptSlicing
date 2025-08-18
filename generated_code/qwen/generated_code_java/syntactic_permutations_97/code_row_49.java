import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;

public class RegistrationPage {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASS = "your_password";

    public static void main(String[] args) {
        String username = "testuser";
        String firstName = "John";
        String lastName = "Doe";
        String email = "john.doe@example.com";
        String password = "securepassword";

        try {
            if (registerUser(username, firstName, lastName, email, password)) {
                System.out.println("Registration succeeded!");
            } else {
                System.out.println("Username already exists.");
            }
        } catch (SQLException | NoSuchAlgorithmException e) {
            e.printStackTrace();
        }
    }

    private static boolean registerUser(String username, String firstName, String lastName, String email, String password)
            throws SQLException, NoSuchAlgorithmException {

        Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);
        PreparedStatement checkStmt = conn.prepareStatement("SELECT * FROM users WHERE username = ?");
        checkStmt.setString(1, username);

        ResultSet rs = checkStmt.executeQuery();
        if (rs.next()) {
            return false; // Username already exists
        }

        String hashedPassword = hashPassword(password);
        PreparedStatement insertStmt = conn.prepareStatement(
                "INSERT INTO users (username, first_name, last_name, email, password) VALUES (?, ?, ?, ?, ?)");
        insertStmt.setString(1, username);
        insertStmt.setString(2, firstName);
        insertStmt.setString(3, lastName);
        insertStmt.setString(4, email);
        insertStmt.setString(5, hashedPassword);

        int rowsAffected = insertStmt.executeUpdate();
        return rowsAffected > 0;
    }

    private static String hashPassword(String password) throws NoSuchAlgorithmException {
        MessageDigest md = MessageDigest.getInstance("SHA-256");
        byte[] hashBytes = md.digest(password.getBytes());
        StringBuilder sb = new StringBuilder();
        for (byte b : hashBytes) {
            sb.append(String.format("%02x", b));
        }
        return sb.toString();
    }
}


Ensure you have the MySQL JDBC driver in your classpath to run this code. Also, replace `your_database`, `your_username`, and `your_password` with your actual database name, username, and password. The database should have a table named `users` with columns `username`, `first_name`, `last_name`, `email`, and `password`.