// Imports for login
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import javax.servlet.http.Cookie;

public class Login {
    private String username;
    private String password;

    // Setters for the login
    public void setUsername(String username) {
        this.username = username;
    }

    public void setPassword(String password) {
        this.password = password;
    }

    // Getter for the username
    public String getUsername() {
        return username;
    }

    // Query to check if the username exists
    public boolean checkUsername() throws SQLException {
        Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);
        PreparedStatement pstmt = conn.prepareStatement("SELECT * FROM users WHERE username=?");
        pstmt.setString(1, username);
        ResultSet rs = pstmt.executeQuery();
        return rs.next();
    }

    // Query to check if the password is correct
    public boolean checkPassword() throws SQLException {
        Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);
        PreparedStatement pstmt = conn.prepareStatement("SELECT * FROM users WHERE username=? AND password=?");
        pstmt.setString(1, username);
        pstmt.setString(2, password);
        ResultSet rs = pstmt.executeQuery();
        return rs.next();
    }
}