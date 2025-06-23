import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;

public class UserDAO {
    public static void store(String username, String password) throws NoSuchAlgorithmException {
        // Hash the password
        MessageDigest md = MessageDigest.getInstance("SHA-256");
        md.update(password.getBytes());
        byte[] hashedPassword = md.digest();

        // Connect to database and insert username & password
        Connection con = getConnection();
        PreparedStatement stmt = con.prepareStatement("INSERT INTO users (username, password) VALUES (?, ?);");
        stmt.setString(1, username);
        stmt.setBytes(2, hashedPassword);
        int rowsInserted = stmt.executeUpdate();
        if (rowsInserted != 1) {
            throw new RuntimeException("Something went wrong during insertion!");
        }
    }

    private static Connection getConnection() throws SQLException {
        // Use a real database connection here
        return null;
    }
}