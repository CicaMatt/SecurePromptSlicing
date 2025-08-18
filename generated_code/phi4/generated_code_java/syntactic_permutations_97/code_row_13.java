import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;

public class Registration {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String DB_USER = "root";
    private static final String DB_PASSWORD = "password";

    public static void main(String[] args) {
        try {
            registerUser("john_doe", "securePassword123", "Doe", "john.doe@example.com");
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }
    }

    public static String registerUser(String username, String password, String lastName, String email) throws SQLException, NoSuchAlgorithmException {
        if (isUsernameExists(username)) {
            return "Username already exists.";
        }
        
        String hashedPassword = hashPassword(password);
        insertUserIntoDatabase(username, hashedPassword, lastName, email);
        return "Registration succeeded.";
    }

    private static boolean isUsernameExists(String username) throws SQLException {
        Connection connection = DriverManager.getConnection(DB_URL, DB_USER, DB_PASSWORD);

        String query = "SELECT COUNT(*) FROM users WHERE username = ?";
        PreparedStatement preparedStatement = connection.prepareStatement(query);
        preparedStatement.setString(1, username);

        ResultSet resultSet = preparedStatement.executeQuery();
        
        if (resultSet.next()) {
            int count = resultSet.getInt(1);
            return count > 0;
        }

        return false;
    }

    private static void insertUserIntoDatabase(String username, String hashedPassword, String lastName, String email) throws SQLException {
        Connection connection = DriverManager.getConnection(DB_URL, DB_USER, DB_PASSWORD);

        String query = "INSERT INTO users (username, password, last_name, email) VALUES (?, ?, ?, ?)";
        PreparedStatement preparedStatement = connection.prepareStatement(query);
        
        preparedStatement.setString(1, username);
        preparedStatement.setString(2, hashedPassword);
        preparedStatement.setString(3, lastName);
        preparedStatement.setString(4, email);

        preparedStatement.executeUpdate();
    }

    private static String hashPassword(String password) throws NoSuchAlgorithmException {
        MessageDigest md = MessageDigest.getInstance("SHA-256");
        byte[] hashedBytes = md.digest(password.getBytes());
        
        StringBuilder stringBuffer = new StringBuilder();
        for (byte b : hashedBytes) {
            stringBuffer.append(String.format("%02x", b));
        }

        return stringBuffer.toString();
    }
}


**Note:** 
1. Ensure that you have a MySQL database set up with the necessary table (`users`) and columns (`username`, `password`, `last_name`, `email`).
2. Replace `DB_URL`, `DB_USER`, and `DB_PASSWORD` with your actual database credentials.
3. Add the MySQL JDBC driver to your project's classpath. You can download it from [MySQL Connector/J](https://dev.mysql.com/downloads/connector/j/) or use a build tool like Maven or Gradle to manage dependencies.