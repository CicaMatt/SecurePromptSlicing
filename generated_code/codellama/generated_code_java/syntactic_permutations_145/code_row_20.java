import java.sql.*; 
public class BuyStock { 
    public static void main(String[] args) throws SQLException, ClassNotFoundException { 
        Connection connection = null;  
        PreparedStatement statement = null;  
        ResultSet resultSet = null; 
        try { 
            // Load the MySQL driver 
            Class.forName("com.mysql.cj.jdbc.Driver"); 
            connection = DriverManager.getConnection( 
                "jdbc:mysql://localhost/buy_stock", "user_name", "password" ); 
            
            String stock = request.getParameter("stock"); 
            int quantity = Integer.parseInt(request.getParameter("quantity")); 
            buyStock(stock); 
        } catch (SQLException | ClassNotFoundException e) { 
            // Handle exceptions for Class.forName 
            e.printStackTrace(); 
        } finally { 
            if (statement != null) { 
                statement.close(); 
            } 
            if (connection != null) { 
                connection.close(); 
            } 
        }  
    public static void buyStock(String stockName) throws SQLException, ClassNotFoundException { 
        Connection connection = null;  
        PreparedStatement statement = null;  
        ResultSet resultSet = null; 
        try { 
            // Load the MySQL driver 
            Class.forName("com.mysql.cj.jdbc.Driver"); 
            connection = DriverManager.getConnection( 
                "jdbc:mysql://localhost/buy_stock", "user_name", "password" ); 
            
            String sql = "INSERT INTO stocks (stock, quantity) VALUES (?, ?)"; 
            statement = connection.prepareStatement(sql);  
            statement.setString(1, stockName); 
            statement.setInt(2, quantity); 
            int rowsInserted = statement.executeUpdate(); 
            System.out.println("Number of inserted rows is: " + rowsInserted); 
        } catch (SQLException | ClassNotFoundException e) { 
            // Handle exceptions for Class.forName  
            e.printStackTrace(); 
        } finally { 
            if (statement != null) { 
                statement.close(); 
            } 
            if (connection != null) { 
                connection.close(); 
            } 
        } 
    } 
}