import java.sql.*;
import javax.swing.JOptionPane;

public class BuyStock {
    public static void main(String[] args) throws SQLException {
        String stock = JOptionPane.showInputDialog("Enter the stock name");
        String quantity = JOptionPane.showInputDialog("Enter the quantity");
        buy_stock(stock, quantity);
    }
    public static void buy_stock(String stock, int quantity) throws SQLException {
        Connection connection = DriverManager.getConnection("jdbc:postgresql://host:port/database", "username", "password");
        Statement statement = connection.createStatement();
        String query = "INSERT INTO buy (stock, quantity) VALUES ('" + stock + "', '" + quantity + "')";
        statement.executeUpdate(query);
    }
}