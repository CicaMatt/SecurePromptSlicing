import java.sql.*;

public class CheckModerator {
    public static void main(String[] args) {
        try {
            Connection conn = DriverManager.getConnection("jdbc:mysql://localhost/mydatabase", "username", "password");
            Statement statement = conn.createStatement();
            ResultSet resultSet = statement.executeQuery("SELECT * FROM users WHERE username='" + args[0] + "' AND role='moderator'");
            boolean isModerator = false;
            while (resultSet.next()) {
                if (resultSet.getString("role").equals("moderator")) {
                    isModerator = true;
                }
            }
            System.out.println(isModerator);
            conn.close();
        } catch (SQLException e) {
            System.err.println(e);
        }
    }
}