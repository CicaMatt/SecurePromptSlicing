import java.io.IOException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.util.Scanner;

public class StockPurchaseApp {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/stock_db";
    private static final String USER = "root";
    private static final String PASS = "password";

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        System.out.print("Enter stock name: ");
        String stockName = scanner.nextLine();
        
        System.out.print("Enter quantity: ");
        int quantity = Integer.parseInt(scanner.nextLine());
        
        buyOrder(stockName, quantity);
    }

    private static void buyOrder(String stockName, int quantity) {
        try (Connection connection = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String sql = "INSERT INTO orders (stock_name, quantity) VALUES (?, ?)";
            
            try (PreparedStatement statement = connection.prepareStatement(sql)) {
                statement.setString(1, stockName);
                statement.setInt(2, quantity);
                
                int rowsInserted = statement.executeUpdate();
                if (rowsInserted > 0) {
                    System.out.println("A new order was inserted successfully!");
                    stockView(stockName, quantity);
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private static void stockView(String stockName, int quantity) {
        System.out.println("Stock Name: " + stockName);
        System.out.println("Quantity: " + quantity);
        // Redirect logic can be handled in a web framework; here we just print to console.
    }
}


**Note:** Ensure you have the MySQL JDBC Driver (`mysql-connector-java`) added to your project dependencies. You also need to create a database named `stock_db` and a table named `orders` with appropriate columns for this code to run successfully.