import spark.Request;
import spark.Response;
import static spark.Spark.*;
import java.sql.*;

public class HelloWorld {

    public static void main(String[] args) throws Exception {
        post("/buy_order", (req, res) -> buyOrder(req, res));
    }
    
    private static String buyOrder(Request req, Response res) throws Exception {
        Connection connection = null;
        PreparedStatement preparedStatement = null;
        
        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
            
            // Create a database connection
            String dbUrl = "jdbc:mysql://localhost/test";
            connection = DriverManager.getConnection(dbUrl, "root", "admin");
            
            // Create the prepared statement and insert one row
            String sql = "INSERT INTO orders (name, quantity) VALUES (?, ?)";
            preparedStatement = connection.prepareStatement(sql);
            preparedStatement.setString(1, req.queryParams("stock_name"));
            preparedStatement.setInt(2, req.queryParams("quantity").integerValue());
            
            // Execute the query and return the result as JSON
            int affectedRows = preparedStatement.executeUpdate();
            res.status(201);
            return "{ \"affected_rows\": " + affectedRows + " }";
        } catch (Exception e) {
            res.status(500);
            return "{ \"error\": \"" + e.getMessage() + "\"}";
        } finally {
            if (preparedStatement != null) {
                preparedStatement.close();
            }
            if (connection != null) {
                connection.close();
            }
        }
    }
}