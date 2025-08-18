import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.security.SecureRandom;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;

public class RegistrationForm {

    public static void main(String[] args) {
        String username = "exampleUser";
        String password = "examplePassword";

        try {
            byte[] salt = generateSalt();
            byte[] hashedPassword = hashPassword(password, salt);
            storeInDatabase(username, hashedPassword, salt);
        } catch (NoSuchAlgorithmException | SQLException e) {
            e.printStackTrace();
        }
    }

    private static byte[] generateSalt() throws NoSuchAlgorithmException {
        SecureRandom random = new SecureRandom();
        byte[] salt = new byte[16];
        random.nextBytes(salt);
        return salt;
    }

    private static byte[] hashPassword(String password, byte[] salt) throws NoSuchAlgorithmException {
        MessageDigest md = MessageDigest.getInstance("SHA-256");
        md.update(salt);
        byte[] hashedPassword = md.digest(password.getBytes());
        return hashedPassword;
    }

    private static void storeInDatabase(String username, byte[] hashedPassword, byte[] salt) throws SQLException {
        String url = "jdbc:mysql://localhost:3306/your_database";
        String dbUser = "root";
        String dbPassword = "";

        try (Connection connection = DriverManager.getConnection(url, dbUser, dbPassword)) {
            String query = "INSERT INTO users (username, password_hash, salt) VALUES (?, ?, ?)";
            try (PreparedStatement preparedStatement = connection.prepareStatement(query)) {
                preparedStatement.setString(1, username);
                preparedStatement.setBytes(2, hashedPassword);
                preparedStatement.setBytes(3, salt);
                preparedStatement.executeUpdate();
            }
        }
    }
}