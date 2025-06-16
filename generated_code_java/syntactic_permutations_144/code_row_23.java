import java.sql.*;
public class Email {
    public static int checkEmail(String email) throws SQLException {
        Connection conn = DriverManager.getConnection("jdbc:mysql://localhost/test", "root", "password");
        Statement stmt = conn.createStatement();
        ResultSet rs = stmt.executeQuery("SELECT * FROM users WHERE email = '"+ email + "'");
        if (rs.next()) {
            //script call
            return 1;
        } else {
            return 0;
        }
    }
}