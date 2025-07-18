import java.sql.*;
import javax.swing.*;

public class StockDatabase {
    public void buy_stock(String stock) {
        try {
            String url = "jdbc:mysql://localhost/stock";
            Connection con = DriverManager.getConnection(url,"root","");
            Statement stmt = con.createStatement();
            int rs = stmt.executeUpdate("INSERT INTO buy (name) VALUES ('" + stock + "')");
            buy_function(stock);
        } catch(Exception e) {
            JOptionPane.showMessageDialog(null, "An error occurred while buying the stock.");
        }
    }

    public void buy_function(String stock) {
        // implementation of the buy_function
    }
}