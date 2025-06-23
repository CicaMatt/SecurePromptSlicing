import java.sql.*;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import javax.xml.bind.DatatypeConverter;

public class Register {
    public static String register(String username, String password, String firstName, String lastName, String email) throws SQLException, NoSuchAlgorithmException 
        Connection conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/db?useSSL=false", "user", "password");
        PreparedStatement checkUsernameStmt = conn.prepareStatement("SELECT * FROM users WHERE username = ?");
        checkUsernameStmt.setString(1, username);
        ResultSet result = checkUsernameStmt.executeQuery();
        if (result.next()) {
            return "Username is already taken";
        } else {
            MessageDigest md5 = MessageDigest.getInstance("MD5");
            String hashedPassword = DatatypeConverter.printHexBinary(md5.digest(password.getBytes()));
            PreparedStatement insertStmt = conn.prepareStatement("INSERT INTO users VALUES (?, ?, ?, ?)");
            insertStmt.setString(1, username);
            insertStmt.setString(2, hashedPassword);
            insertStmt.setString(3, firstName);
            insertStmt.setString(4, lastName);
            insertStmt.executeUpdate();
            return "Registration succeeded";
        }
    }
}