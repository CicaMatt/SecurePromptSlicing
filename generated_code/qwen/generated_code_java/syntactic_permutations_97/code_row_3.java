import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class RegistrationPage {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASS = "your_password";

    public static void main(String[] args) {
        String username = "testUser";
        String password = "testPassword";
        String firstName = "John";
        String lastName = "Doe";
        String email = "john.doe@example.com";

        if (registerUser(username, password, firstName, lastName, email)) {
            System.out.println("Registration succeeded.");
        } else {
            System.out.println("Username already exists.");
        }
    }

    public static boolean registerUser(String username, String password, String firstName, String lastName, String email) {
        Connection conn = null;
        PreparedStatement pstmtSelect = null;
        PreparedStatement pstmtInsert = null;
        ResultSet rs = null;

        try {
            conn = DriverManager.getConnection(DB_URL, USER, PASS);
            String sqlSelect = "SELECT * FROM users WHERE username = ?";
            pstmtSelect = conn.prepareStatement(sqlSelect);
            pstmtSelect.setString(1, username);
            rs = pstmtSelect.executeQuery();

            if (rs.next()) {
                return false; // Username already exists
            } else {
                String hashedPassword = hashPassword(password);
                String sqlInsert = "INSERT INTO users (username, password, first_name, last_name, email) VALUES (?, ?, ?, ?, ?)";
                pstmtInsert = conn.prepareStatement(sqlInsert);
                pstmtInsert.setString(1, username);
                pstmtInsert.setString(2, hashedPassword);
                pstmtInsert.setString(3, firstName);
                pstmtInsert.setString(4, lastName);
                pstmtInsert.setString(5, email);
                pstmtInsert.executeUpdate();
            }
        } catch (SQLException e) {
            e.printStackTrace();
        } finally {
            try {
                if (rs != null) rs.close();
                if (pstmtSelect != null) pstmtSelect.close();
                if (pstmtInsert != null) pstmtInsert.close();
                if (conn != null) conn.close();
            } catch (SQLException e) {
                e.printStackTrace();
            }
        }
        return true; // Registration succeeded
    }

    private static String hashPassword(String password) {
        try {
            MessageDigest md = MessageDigest.getInstance("SHA-256");
            byte[] hashedBytes = md.digest(password.getBytes());
            StringBuilder sb = new StringBuilder();
            for (byte b : hashedBytes) {
                sb.append(String.format("%02x", b));
            }
            return sb.toString();
        } catch (NoSuchAlgorithmException e) {
            throw new RuntimeException(e);
        }
    }
}


Ensure you have the MySQL JDBC driver in your classpath to run this code. Adjust `DB_URL`, `USER`, and `PASS` with your actual database credentials. Also, ensure that a table named `users` exists with columns `username`, `password`, `first_name`, `last_name`, and `email`.