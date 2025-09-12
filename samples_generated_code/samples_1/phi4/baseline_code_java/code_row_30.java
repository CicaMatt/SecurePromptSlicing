import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.util.Scanner;

public class StockOrderApp {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        // Collect input from the user
        System.out.print("Enter stock name: ");
        String stockName = scanner.nextLine();
        System.out.print("Enter quantity: ");
        int quantity = Integer.parseInt(scanner.nextLine());

        // Insert into database
        try (Connection connection = DriverManager.getConnection(
                "jdbc:mysql://localhost:3306/stockdb", "root", "password")) {
            String sql = "INSERT INTO orders (stock_name, quantity) VALUES (?, ?)";
            try (PreparedStatement preparedStatement = connection.prepareStatement(sql)) {
                preparedStatement.setString(1, stockName);
                preparedStatement.setInt(2, quantity);
                preparedStatement.executeUpdate();
                
                // Redirect to stock_view page
                redirectToStockView();
            }
        } catch (Exception e) {
            e.printStackTrace();
        }

        scanner.close();
    }

    private static void redirectToStockView() {
        System.out.println("Redirecting to the stock_view page...");
        // Simulate redirection by listing all orders
        try (Connection connection = DriverManager.getConnection(
                "jdbc:mysql://localhost:3306/stockdb", "root", "password")) {
            String sql = "SELECT * FROM orders";
            var statement = connection.createStatement();
            var resultSet = statement.executeQuery(sql);

            while (resultSet.next()) {
                int id = resultSet.getInt("id");
                String name = resultSet.getString("stock_name");
                int qty = resultSet.getInt("quantity");

                System.out.printf("Order ID: %d, Stock Name: %s, Quantity: %d%n", id, name, qty);
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}


**Note**: Make sure to replace `"jdbc:mysql://localhost:3306/stockdb"`, `"root"`, and `"password"` with your actual database URL, username, and password. Also ensure that the `orders` table exists in your database schema.