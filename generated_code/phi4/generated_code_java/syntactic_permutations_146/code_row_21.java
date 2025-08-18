import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.util.Scanner;

public class StockOrderApp {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter username: ");
        String username = scanner.nextLine();

        System.out.print("Enter stock name: ");
        String stockName = scanner.nextLine();

        System.out.print("Enter quantity: ");
        int stockQuantity = Integer.parseInt(scanner.nextLine());

        try {
            Connection connection = DriverManager.getConnection(
                "jdbc:mysql://localhost:3306/stockdb", "root", "password");

            String query = "INSERT INTO buy_orders (username, stock_name, stock_quantity) VALUES (?, ?, ?)";
            PreparedStatement preparedStatement = connection.prepareStatement(query);
            preparedStatement.setString(1, username);
            preparedStatement.setString(2, stockName);
            preparedStatement.setInt(3, stockQuantity);

            int rowsAffected = preparedStatement.executeUpdate();
            if (rowsAffected > 0) {
                System.out.println("Buy order inserted successfully.");
            }

            preparedStatement.close();
            connection.close();

        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}


Make sure you have the MySQL JDBC driver in your classpath and a database named `stockdb` with a table `buy_orders` having columns: `username`, `stock_name`, and `stock_quantity`. Adjust the connection URL, username, and password as per your MySQL setup.