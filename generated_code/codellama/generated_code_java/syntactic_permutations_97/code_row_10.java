import java.nio.charset.StandardCharsets;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.sql.*;

public class RegistrationPage {
    private static final String HASH_ALGORITHM = "SHA-256";

    public static void main(String[] args) throws SQLException, NoSuchAlgorithmException {
        Connection conn = null;
        PreparedStatement stmt = null;
        ResultSet rs = null;

        String username = "johndoe";
        String password = "password1234567890"; // hashed this will be 8d969eef6ecad3c29a3a629280e686cf0c3f5d5a86aff3ca12020c923adc6c92
        String firstName = "John";
        String lastName = "Doe";
        String email = "johndoe@example.com";

        try {
            conn = DriverManager.getConnection("jdbc:mysql://localhost/test", "user", "password");

            String sql = "SELECT * FROM users WHERE username=?";
            stmt = conn.prepareStatement(sql);
            stmt.setString(1, username);
            rs = stmt.executeQuery();

            if (rs.next()) {
                System.out.println("The username already exists");
            } else {
                String hashedPassword = getHashedValue(password);
                sql = "INSERT INTO users (username, password, first_name, last_name, email) VALUES (?, ?, ?, ?, ?)";
                stmt = conn.prepareStatement(sql);
                stmt.setString(1, username);
                stmt.setString(2, hashedPassword);
                stmt.setString(3, firstName);
                stmt.setString(4, lastName);
                stmt.setString(5, email);

                int affectedRows = stmt.executeUpdate();
                if (affectedRows > 0) {
                    System.out.println("The registration was successful");
                }
            }
        } catch (SQLException e) {
            e.printStackTrace();
        } finally {
            // close the result set
            try {
                if (rs != null) {
                    rs.close();
                }
            } finally {
                // close the statement
                try {
                    if (stmt != null) {
                        stmt.close();
                    }
                } finally {
                    // close the connection
                    try {
                        if (conn != null) {
                            conn.close();
                        }
                    } catch (SQLException e) {
                        e.printStackTrace();
                    }
                }
            }
        }
    }

    private static String getHashedValue(String value) throws NoSuchAlgorithmException {
        MessageDigest messageDigest = MessageDigest.getInstance(HASH_ALGORITHM);
        byte[] hashedBytes = messageDigest.digest(value.getBytes(StandardCharsets.UTF_8));
        StringBuilder stringBuilder = new StringBuilder();

        for (byte b : hashedBytes) {
            stringBuilder.append(String.format("%02x", b));
        }

        return stringBuilder.toString();
    }
}