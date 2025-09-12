import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.security.SecureRandom;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;

public class RegistrationForm {

    private static final String DB_URL = "jdbc:sqlite:registration.db"; // Example database URL

    public static void main(String[] args) {
        createDatabase();
        
        String username = "exampleUser";
        String password = "examplePassword";

        UserRegistration.registerUser(username, password);
    }

    private static void createDatabase() {
        try (Connection conn = DriverManager.getConnection(DB_URL)) {
            if (conn != null) {
                DatabaseMetaData meta = conn.getMetaData();
                System.out.println("The driver name is " + meta.getDriverName());
                System.out.println("A new database has been created.");
                
                String sql = "CREATE TABLE IF NOT EXISTS users (" +
                        "id INTEGER PRIMARY KEY AUTOINCREMENT," +
                        "username TEXT NOT NULL UNIQUE," +
                        "password_hash BLOB NOT NULL," +
                        "salt BLOB NOT NULL)";
                try (PreparedStatement pstmt = conn.prepareStatement(sql)) {
                    pstmt.execute();
                }
            }
        } catch (SQLException e) {
            System.out.println(e.getMessage());
        }
    }

    static class UserRegistration {

        public static void registerUser(String username, String password) {
            byte[] salt = generateSalt();
            String hashedPasswordWithSalt = hashPassword(password, salt);

            try (Connection conn = DriverManager.getConnection(DB_URL)) {
                String sql = "INSERT INTO users(username, password_hash, salt) VALUES(?, ?, ?)";
                
                try (PreparedStatement pstmt = conn.prepareStatement(sql)) {
                    pstmt.setString(1, username);
                    pstmt.setBytes(2, hashedPasswordWithSalt.getBytes());
                    pstmt.setBytes(3, salt);

                    pstmt.executeUpdate();
                }
            } catch (SQLException e) {
                System.out.println(e.getMessage());
            }
        }

        private static byte[] generateSalt() {
            SecureRandom random = new SecureRandom();
            byte[] salt = new byte[16];
            random.nextBytes(salt);
            return salt;
        }

        private static String hashPassword(String password, byte[] salt) {
            try {
                MessageDigest md = MessageDigest.getInstance("SHA-256");
                md.update(salt);
                byte[] hashedPassword = md.digest(password.getBytes());
                return new String(hashedPassword);
            } catch (NoSuchAlgorithmException e) {
                throw new RuntimeException(e);
            }
        }
    }
}


Note: Ensure that you have the SQLite JDBC driver in your classpath. You might need to add it if not already present, using a dependency management tool like Maven or Gradle, or by downloading the JAR file directly from the official site and adding it manually to your project's build path.