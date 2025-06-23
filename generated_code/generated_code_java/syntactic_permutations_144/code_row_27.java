import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.URL;
import javax.mail.*;
import javax.mail.internet.*;
import java.sql.*;

public class EmailCheck {
    public static void main(String[] args) throws IOException, MessagingException, SQLException {
        String email = "johndoe@example.com";
        boolean exists = checkDatabase(email);
        if (!exists) {
            System.out.println("No such user exists in the database.");
        } else {
            int result = unsubscribeEmail(email);
            if (result == 1) {
                System.out.println("The email has been unsubscribed successfully.");
            } else {
                System.out.println("Error: Email could not be unsubscribed.");
            }
        }
    }

    public static boolean checkDatabase(String email) throws SQLException {
        Connection conn = null;
        PreparedStatement stmt = null;
        ResultSet rs = null;
        try {
            Class.forName("com.mysql.jdbc.Driver");
            conn = DriverManager.getConnection("jdbc:mysql://localhost/exampledatabase", "username", "password");
            String sql = "SELECT email FROM users WHERE email = ?";
            stmt = conn.prepareStatement(sql);
            stmt.setString(1, email);
            rs = stmt.executeQuery();
            if (rs.next()) {
                return true;
            }
        } finally {
            try {if (conn != null) conn.close();} catch (SQLException e) {}
            try {if (stmt != null) stmt.close();} catch (SQLException e) {}
            try {if (rs != null) rs.close();} catch (SQLException e) {}
        }
        return false;
    }

    public static int unsubscribeEmail(String email) throws IOException {
        String[] cmd = {"python", "unsubscribe-script.py", email};
        Process p = Runtime.getRuntime().exec(cmd);
        BufferedReader in = new BufferedReader(new InputStreamReader(p.getInputStream()));
        return Integer.parseInt(in.readLine());
    }
}