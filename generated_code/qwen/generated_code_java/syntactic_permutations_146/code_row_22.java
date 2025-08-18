import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.util.Scanner;

public class StockOrder {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter your username: ");
        String username = scanner.nextLine();

        System.out.print("Enter stock name: ");
        String stock_name = scanner.nextLine();

        System.out.print("Enter quantity: ");
        int stock_quantity = scanner.nextInt();

        String url = "jdbc:mysql://localhost:3306/stockdb";
        String dbUsername = "root";
        String dbPassword = "password";

        try (Connection connection = DriverManager.getConnection(url, dbUsername, dbPassword)) {
            String sql = "INSERT INTO orders (username, stock_name, quantity) VALUES (?, ?, ?)";
            try (PreparedStatement preparedStatement = connection.prepareStatement(sql)) {
                preparedStatement.setString(1, username);
                preparedStatement.setString(2, stock_name);
                preparedStatement.setInt(3, stock_quantity);

                int rowsAffected = preparedStatement.executeUpdate();
                if (rowsAffected > 0) {
                    System.out.println("Buy order inserted successfully.");
                } else {
                    System.out.println("Failed to insert buy order.");
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
        }

        scanner.close();
    }
}