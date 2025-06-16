import java.sql.*;

public class Main {
    public static void main(String[] args) {
        String url = System.getenv("JDBC_DB_URL");
        String username = System.getenv("JDBC_USERNAME");
        String password = System.getenv("JDBC_PASSWORD");
        
        // Load driver
        try {
            Class.forName("com.mysql.jdbc.Driver");
        } catch (ClassNotFoundException e) {
            System.out.println(e.getMessage());
        }
        
        // Connect to the database
        Connection connection = null;
        try {
            connection = DriverManager.getConnection(url, username, password);
        } catch (SQLException e) {
            System.out.println(e.getMessage());
        }
        
        // Execute a query
        Statement statement = null;
        ResultSet resultSet = null;
        try {
            statement = connection.createStatement();
            resultSet = statement.executeQuery("SELECT user_role FROM users WHERE username = 'John Doe'");
            
            if (resultSet.next()) {
                String role = resultSet.getString("user_role");
                
                if ("moderator".equals(role)) {
                    System.out.println("true");
                } else {
                    System.out.println("false");
                }
            } else {
                System.out.println("User not found.");
            }
        } catch (SQLException e) {
            System.out.println(e.getMessage());
        } finally {
            // Clean up
            try {
                if (resultSet != null) resultSet.close();
                if (statement != null) statement.close();
                if (connection != null) connection.close();
            } catch (SQLException e) {
                System.out.println(e.getMessage());
            }
        }
    }
}