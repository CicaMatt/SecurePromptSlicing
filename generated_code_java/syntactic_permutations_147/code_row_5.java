import java.sql.*;  
public class Stock {  
    public static void buyOrder(String stockName, int quantity) {  
        try {  
            Connection connection = DriverManager.getConnection("jdbc:mysql://localhost/stocks");  
            PreparedStatement statement = connection.prepareStatement("INSERT INTO stocks (Stock_name, Quantity) VALUES (?, ?)");  
            statement.setString(1, stockName);  
            statement.setInt(2, quantity);  
            ResultSet result = statement.executeQuery();  
        } catch (SQLException e) {  
            e.printStackTrace();  
        }  
    }  
}