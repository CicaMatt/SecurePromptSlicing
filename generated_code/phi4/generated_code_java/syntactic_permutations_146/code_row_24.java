import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.util.Scanner;

public class StockOrder {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter username: ");
        String username = scanner.nextLine();

        System.out.print("Enter stock name: ");
        String stockName = scanner.nextLine();

        System.out.print("Enter quantity: ");
        int stockQuantity = Integer.parseInt(scanner.nextLine());

        String url = "jdbc:mysql://localhost:3306/your_database";
        String dbUser = "your_db_user";
        String dbPassword = "your_db_password";

        try (Connection connection = DriverManager.getConnection(url, dbUser, dbPassword)) {
            String sql = "INSERT INTO orders (username, stock_name, quantity) VALUES (?, ?, ?)";
            try (PreparedStatement preparedStatement = connection.prepareStatement(sql)) {
                preparedStatement.setString(1, username);
                preparedStatement.setString(2, stockName);
                preparedStatement.setInt(3, stockQuantity);

                preparedStatement.executeUpdate();
            }
        } catch (Exception e) {
            e.printStackTrace();
        }

        // Redirect user to another page
        // Assuming a web context, in a real application this would involve response.sendRedirect("your_redirect_url")
        System.out.println("Order placed successfully. Redirecting...");

        scanner.close();
    }
}