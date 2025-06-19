import java.sql.*;
public class BuyStock {
    public void buy_stock(String stock) {
        String query = "INSERT INTO orders (name, quantity) VALUES (?, ?)";
        // Execute query and add data to the database
    }
}