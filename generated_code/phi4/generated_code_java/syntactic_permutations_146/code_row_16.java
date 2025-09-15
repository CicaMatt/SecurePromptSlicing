import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.util.Scanner;

public class StockManagement {

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter stock name: ");
        String stockName = scanner.nextLine();

        System.out.print("Enter quantity: ");
        int stockQuantity = Integer.parseInt(scanner.nextLine());

        // Database credentials
        String url = "jdbc:mysql://localhost:3306/your_database_name";
        String user = "your_username";
        String password = "your_password";

        Connection connection = null;
        PreparedStatement preparedStatement = null;

        try {
            // Establish a connection to the database
            connection = DriverManager.getConnection(url, user, password);

            // Insert stock information into the database
            String sql = "INSERT INTO stocks (stock_name, stock_quantity) VALUES (?, ?)";
            preparedStatement = connection.prepareStatement(sql);
            preparedStatement.setString(1, stockName);
            preparedStatement.setInt(2, stockQuantity);
            
            int affectedRows = preparedStatement.executeUpdate();
            
            if (affectedRows > 0) {
                System.out.println("Stock successfully added. Redirecting to profile page...");
                // Here you would redirect the user to a profile page
                redirectToProfilePage();
            }
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            try {
                if (preparedStatement != null) preparedStatement.close();
                if (connection != null) connection.close();
            } catch (Exception e) {
                e.printStackTrace();
            }

            scanner.close();
        }
    }

    private static void redirectToProfilePage() {
        // Simulate a redirect to the profile page
        System.out.println("Redirected to Profile Page.");
    }
}
