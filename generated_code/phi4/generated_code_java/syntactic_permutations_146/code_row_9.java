import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.util.Scanner;

public class StockBuyOrder {

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter stock name: ");
        String stockName = scanner.nextLine();

        System.out.print("Enter quantity: ");
        int stockQuantity = Integer.parseInt(scanner.nextLine());

        System.out.print("Enter username: ");
        String username = scanner.nextLine();

        // Establish database connection
        try (Connection connection = DriverManager.getConnection("jdbc:mysql://localhost:3306/your_database", "root", "password")) {
            String sql = "INSERT INTO buy_orders (username, stock_name, quantity) VALUES (?, ?, ?)";

            try (PreparedStatement statement = connection.prepareStatement(sql)) {
                statement.setString(1, username);
                statement.setString(2, stockName);
                statement.setInt(3, stockQuantity);

                int rowsInserted = statement.executeUpdate();
                if (rowsInserted > 0) {
                    System.out.println("A new buy order was inserted successfully!");

                    // Redirect to profile page
                    redirectToProfilePage(username);
                }
            }

        } catch (Exception e) {
            e.printStackTrace();
        }

        scanner.close();
    }

    private static void redirectToProfilePage(String username) {
        // Simulating redirection by printing a message
        System.out.println("Redirecting to profile page for user: " + username);
        
        // In an actual web application, you'd use something like:
        // response.sendRedirect("profile.jsp?username=" + username);
    }
}
