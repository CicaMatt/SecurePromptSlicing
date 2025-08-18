import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class RegistrationPage {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String DB_USER = "your_username";
    private static final String DB_PASSWORD = "your_password";

    public static void main(String[] args) {
        String username = "testuser";
        String password = "password123";
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
        Connection connection = null;
        PreparedStatement checkStatement = null;
        PreparedStatement insertStatement = null;
        ResultSet resultSet = null;

        try {
            connection = DriverManager.getConnection(DB_URL, DB_USER, DB_PASSWORD);
            String hashedPassword = hashPassword(password);

            String checkQuery = "SELECT 1 FROM users WHERE username = ?";
            checkStatement = connection.prepareStatement(checkQuery);
            checkStatement.setString(1, username);
            resultSet = checkStatement.executeQuery();

            if (resultSet.next()) {
                return false; // Username already exists
            }

            String insertQuery = "INSERT INTO users (username, password, first_name, last_name, email) VALUES (?, ?, ?, ?, ?)";
            insertStatement = connection.prepareStatement(insertQuery);
            insertStatement.setString(1, username);
            insertStatement.setString(2, hashedPassword);
            insertStatement.setString(3, firstName);
            insertStatement.setString(4, lastName);
            insertStatement.setString(5, email);

            int rowsAffected = insertStatement.executeUpdate();
            return rowsAffected > 0;

        } catch (SQLException e) {
            e.printStackTrace();
        } finally {
            try {
                if (resultSet != null) resultSet.close();
                if (checkStatement != null) checkStatement.close();
                if (insertStatement != null) insertStatement.close();
                if (connection != null) connection.close();
            } catch (SQLException e) {
                e.printStackTrace();
            }
        }
        return false;
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
            throw new RuntimeException("SHA-256 algorithm not found", e);
        }
    }
}



<!-- Add this to your pom.xml if you are using Maven -->
<dependencies>
    <dependency>
        <groupId>mysql</groupId>
        <artifactId>mysql-connector-java</artifactId>
        <version>8.0.33</version>
    </dependency>
</dependencies>