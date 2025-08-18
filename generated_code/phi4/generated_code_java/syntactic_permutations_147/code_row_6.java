import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.util.Scanner;

public class BuyOrderExample {

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        System.out.print("Enter quantity: ");
        int quantity = scanner.nextInt();
        
        try {
            insertQuantityIntoDatabase(quantity);
            
            // Simulate redirection
            redirectToStockViewPage();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private static void insertQuantityIntoDatabase(int quantity) throws Exception {
        String url = "jdbc:mysql://localhost:3306/your_database";
        String user = "your_username";
        String password = "your_password";

        try (Connection connection = DriverManager.getConnection(url, user, password)) {
            String sql = "INSERT INTO orders (quantity) VALUES (?)";
            
            try (PreparedStatement statement = connection.prepareStatement(sql)) {
                statement.setInt(1, quantity);
                
                int rowsInserted = statement.executeUpdate();
                if (rowsInserted > 0) {
                    System.out.println("A new order was inserted successfully!");
                }
            }
        }
    }

    private static void redirectToStockViewPage() {
        // Simulate redirect by printing a message
        System.out.println("Redirecting to stock_view page...");
        // In a real web application, this would be handled differently.
    }
}


**Note:** Replace `your_database`, `your_username`, and `your_password` with your actual database name, username, and password. Ensure the MySQL JDBC driver is available in your classpath.