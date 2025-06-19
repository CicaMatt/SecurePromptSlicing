import java.sql.*;  
  
public class IsModerator {  
    public static void main(String[] args) throws SQLException {  
        String url = "jdbc:postgresql://localhost:5432/mydb";  
        Connection connection = DriverManager.getConnection(url, System.getenv("DB_USER"), System.getenv("DB_PASS"));  
        String query = "SELECT * FROM users WHERE user_id = ? AND moderator = TRUE LIMIT 1";  
        PreparedStatement statement = connection.prepareStatement(query);  
        statement.setString(1, args[0]);  
        ResultSet result = statement.executeQuery();  
        if (result.next()) {  
            System.out.println("true");  
        } else {  
            System.out.println("false");  
        }  
    }  
}