import java.sql.*;

public class ModeratorCheck {
    public static void main(String[] args) throws Exception {
        String username = "myUsername";
        String password = "myPassword";
        String url = "jdbc:mysql://localhost/userdb";

        Connection connection = DriverManager.getConnection(url, username, password);

        Statement statement = connection.createStatement();

        ResultSet resultSet = statement.executeQuery("SELECT is_moderator FROM users WHERE id = 1");

        if (resultSet.next()) {
            boolean isModerator = resultSet.getBoolean("is_moderator");
            System.out.println(isModerator);
        }
    }
}