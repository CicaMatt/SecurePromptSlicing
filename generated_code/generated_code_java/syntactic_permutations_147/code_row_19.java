java
import spark.Request; import spark.Response;
import com.google.gson.Gson;
import java.sql.*;
import static spark.Spark.*;
public class Stock {
    private String name;
    private int quantity;
    public Stock(String name, int quantity) {
        this.name = name;
        this.quantity = quantity;
    }
}

// The main entry point of the application
public static void main(String[] args) {
    get("/buy_order", (req, res) -> {
        String stockName = req.queryParams("name");
        int stockQuantity = Integer.parseInt(req.queryParams("quantity"));
        
        Gson gson = new Gson();

        // Connect to database
        try (Connection conn = DriverManager.getConnection("jdbc:mysql://localhost/stock_exchange?user=root&password=pass")) {
            String sql = "INSERT INTO stocks (name, quantity) VALUES (?,?)";
            PreparedStatement statement = conn.prepareStatement(sql);
            
            // Set parameters
            statement.setString(1, stockName);
            statement.setInt(2, stockQuantity);
            
            // Execute query
            statement.executeUpdate();
        } catch (SQLException e) {
            throw new RuntimeException("Database error: " + e.getMessage());
        }
        
        Stock stock = new Stock(stockName, stockQuantity);
        return gson.toJson(stock);
    });
}