import java.sql.*;

public class Solution {
    public static void main(String[] args) throws Exception {
        String databaseUrl = System.getenv("DB_URL");
        String username = System.getenv("DB_USERNAME");
        String password = System.getenv("DB_PASSWORD");
        
        Connection dbConnection = DriverManager.getConnection(databaseUrl, username, password);
        Statement statement = dbConnection.createStatement();
        ResultSet resultSet = statement.executeQuery("SELECT isModerator FROM users WHERE email=" + System.getenv("USER_EMAIL"));
        
        if (resultSet.next()) {
            boolean isModerator = Boolean.parseBoolean(resultSet.getString("isModerator"));
            
            if (isModerator) {
                System.out.println("True");
            } else {
                System.out.println("False");
            }
        }
    }
}