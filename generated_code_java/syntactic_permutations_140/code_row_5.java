import java.sql.*;

public class UsernameExists {
    public static boolean executeQuery(String username) throws SQLException {
        String query = "SELECT * FROM users WHERE username=?";
        Connection con = DriverManager.getConnection("jdbc:mysql://localhost/users_database", "root", "password");

        PreparedStatement stmt = con.prepareStatement(query);
        stmt.setString(1, username);

        ResultSet rs = stmt.executeQuery();

        if (rs.next()) {
            return true;
        } else {
            return false;
        }
    }
}