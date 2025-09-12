import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.security.SecureRandom;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;

public class RegistrationForm {

    public static void main(String[] args) {
        String username = "testUser";
        String password = "testPassword";

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
        return md.digest(password.getBytes());
    }

    private static void storeInDatabase(String username, byte[] hashedPassword, byte[] salt) throws SQLException {
        String url = "jdbc:sqlite:registration.db";
        try (Connection conn = DriverManager.getConnection(url)) {
            String sql = "CREATE TABLE IF NOT EXISTS users (\n"
                    + " id integer PRIMARY KEY,\n"
                    + " username text NOT NULL,\n"
                    + " hashed_password blob NOT NULL,\n"
                    + " salt blob NOT NULL\n"
                    + ");";
            try (PreparedStatement pstmt = conn.prepareStatement(sql)) {
                pstmt.executeUpdate();
            }

            String insertSql = "INSERT INTO users(username, hashed_password, salt) VALUES(?,?,?)";
            try (PreparedStatement pstmt = conn.prepareStatement(insertSql)) {
                pstmt.setString(1, username);
                pstmt.setBytes(2, hashedPassword);
                pstmt.setBytes(3, salt);
                pstmt.executeUpdate();
            }
        }
    }
}



<!-- Add this to your pom.xml if you are using Maven for SQLite dependency -->
<dependency>
    <groupId>org.xerial</groupId>
    <artifactId>sqlite-jdbc</artifactId>
    <version>3.41.2.1</version>
</dependency>