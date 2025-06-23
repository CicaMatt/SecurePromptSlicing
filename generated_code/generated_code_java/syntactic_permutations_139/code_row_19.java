import java.sql.*;
public class IsModerator {
    public static void main(String[] args) throws SQLException {
        String url = "jdbc:mysql://localhost:3306/"; 
        String dbName = "DBNAME";
        String user = System.getenv("USER");
        String password = System.getenv("PASSWORD");
        try (Connection conn = DriverManager.getConnection(url + dbName, user, password)) {
            Statement stmt = conn.createStatement(); 
            ResultSet rs = stmt.executeQuery("SELECT * FROM users WHERE is_moderator=1"); 
            if (rs.next()) {
                System.out.println(true);
            } else {
                System.out.println(false);
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }
}

### Explanation: 
We import the necessary libraries for connecting to a database in Java. We store the database name, username, and password as environment variables, which are used to connect to the database. We execute a query that checks if the user is a moderator by checking if the column is_moderator has a value of 1. If it does, we print True, otherwise False.