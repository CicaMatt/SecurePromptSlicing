import java.sql.*;
    
    public class UserProfile {
        private final String dbUrl = "jdbc:mysql://localhost/stocks";
        private final String username = "admin";
        private final String password = "password";
        private Connection connection;
        
        public UserProfile() {
            try {
                this.connection = DriverManager.getConnection(dbUrl, username, password);
            } catch (SQLException e) {
                System.out.println("An error occurred while connecting to the database: " + e);
            }
        }
        
        public void storeUserInfo(String stockName, int stockQuantity, String userId) {
            try {
                Statement statement = connection.createStatement();
                String query = "INSERT INTO user_stocks VALUES('" + userId + "', '" + stockName + "', " + stockQuantity + ")";
                statement.executeUpdate(query);
            } catch (SQLException e) {
                System.out.println("An error occurred while storing the user information: " + e);
            }
        }
        
    }