import java.sql.*;

public class Main {
    public static void main(String[] args) throws ClassNotFoundException, SQLException {
        String url = System.getenv("DB_URL");
        String username = System.getenv("DB_USERNAME");
        String password = System.getenv("DB_PASSWORD");

        Connection connection = DriverManager.getConnection(url, username, password);

        Statement statement = connection.createStatement();
        ResultSet resultSet = statement.executeQuery("SELECT role FROM users WHERE id = 1");
        while (resultSet.next()) {
            String role = resultSet.getString("role");
            if (role.equals("moderator")) {
                System.out.println(true);
            } else {
                System.out.println(false);
            }
        }
    }
}