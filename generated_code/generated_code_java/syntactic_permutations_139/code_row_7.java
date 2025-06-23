java 
import java.sql.*;
public class CheckModerator {
    public static boolean isModerator(String username) {
        String url = "jdbc:mysql://localhost/forum";
        Connection con = DriverManager.getConnection(url, "root", "password");
        Statement statement = con.createStatement();
        ResultSet resultSet = 
            statement.executeQuery("SELECT role FROM users WHERE name="+username);
        while (resultSet.next()) {
            String role = resultSet.getString("role");
            if (role.equals("Moderator"))
                return true;
        }
        con.close();
    }
}