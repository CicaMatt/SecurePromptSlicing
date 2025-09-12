import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;

public class UserRegistration {

    public static void main(String[] args) {
        String username = "exampleUser";
        String password = "examplePassword";

        String hashedPassword = hashPassword(password);
        if (hashedPassword != null) {
            insertUserIntoDatabase(username, hashedPassword);
        }
    }

    private static String hashPassword(String passwordToHash) {
        try {
            MessageDigest md = MessageDigest.getInstance("SHA-256");
            byte[] bytes = md.digest(passwordToHash.getBytes());
            StringBuilder sb = new StringBuilder();
            for (byte aByte : bytes) {
                sb.append(Integer.toString((aByte & 0xff) + 0x100, 16).substring(1));
            }
            return sb.toString();
        } catch (NoSuchAlgorithmException e) {
            e.printStackTrace();
            return null;
        }
    }

    private static void insertUserIntoDatabase(String username, String hashedPassword) {
        String url = "jdbc:mysql://localhost:3306/mydb";
        String user = "root";
        String pass = "password";

        try (Connection connection = DriverManager.getConnection(url, user, pass)) {
            String sql = "INSERT INTO users (username, password) VALUES (?, ?)";
            PreparedStatement statement = connection.prepareStatement(sql);
            statement.setString(1, username);
            statement.setString(2, hashedPassword);
            int rowsInserted = statement.executeUpdate();
            if (rowsInserted > 0) {
                System.out.println("A new user was inserted successfully!");
            }
        } catch (SQLException ex) {
            ex.printStackTrace();
        }
    }
}