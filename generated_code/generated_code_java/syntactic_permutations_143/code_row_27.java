import java.sql.*;

public class UnsubscribeService {
    public static void main(String[] args) throws SQLException {
        String endpoint = "/unsubscribe";
        Connection conn = DriverManager.getConnection("jdbc:mysql://localhost/newsletter", "root", "password");
        Statement statement = conn.createStatement();
        ResultSet resultSet = statement.executeQuery(String.format("SELECT * FROM subscribers WHERE email='%s'", args[0]));
        
        if (resultSet.next()) {
            String sql = String.format("DELETE FROM subscribers WHERE email='%s';", args[0]);
            statement.executeUpdate(sql);
            System.out.println("You have successfully unsubscribed");
        } else {
            System.out.println("You are not a subscriber");
        }
    }
}