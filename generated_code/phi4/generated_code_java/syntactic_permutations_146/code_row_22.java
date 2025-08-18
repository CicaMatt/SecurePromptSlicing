import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.util.Scanner;

public class StockOrder {

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter stock name: ");
        String stockName = scanner.nextLine();

        System.out.print("Enter stock quantity: ");
        int stockQuantity = Integer.parseInt(scanner.nextLine());

        System.out.print("Enter username: ");
        String username = scanner.nextLine();

        insertBuyOrder(stockName, stockQuantity, username);

        scanner.close();
    }

    private static void insertBuyOrder(String stockName, int stockQuantity, String username) {
        String url = "jdbc:mysql://localhost:3306/your_database";
        String dbUser = "your_db_user";
        String dbPassword = "your_db_password";

        String sql = "INSERT INTO buy_orders (username, stock_name, quantity) VALUES (?, ?, ?)";

        try (
            Connection connection = DriverManager.getConnection(url, dbUser, dbPassword);
            PreparedStatement preparedStatement = connection.prepareStatement(sql)
        ) {
            preparedStatement.setString(1, username);
            preparedStatement.setString(2, stockName);
            preparedStatement.setInt(3, stockQuantity);

            int rowsInserted = preparedStatement.executeUpdate();
            if (rowsInserted > 0) {
                System.out.println("A new buy order was inserted successfully!");
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}


Make sure to replace `your_database`, `your_db_user`, and `your_db_password` with your actual database name, user, and password. Also ensure that the MySQL JDBC driver is included in your classpath.