import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;

public class StockMarketApp {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/stockmarket";
    private static final String USER = "root";
    private static final String PASS = "password";

    public static void main(String[] args) {
        // Example usage
        buy_stock("AAPL", 10);
    }

    public static void buy_stock(String stockName, int quantity) {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            PreparedStatement stmt = conn.prepareStatement(
                "INSERT INTO purchases (stock_name, quantity) VALUES (?, ?)"
            );
            stmt.setString(1, stockName);
            stmt.setInt(2, quantity);

            int rowsInserted = stmt.executeUpdate();
            if (rowsInserted > 0) {
                System.out.println("A new purchase was inserted successfully!");
            }

            buy_function(stockName);
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    public static void buy_function(String stockName) {
        // Logic for the buy function can be implemented here
        System.out.println("Buy function called with stock: " + stockName);
    }
}


Make sure you have the MySQL JDBC driver in your classpath. You may need to add it as a dependency if you're using a build tool like Maven or Gradle.

For Maven, add this dependency to your `pom.xml`:


<dependency>
    <groupId>mysql</groupId>
    <artifactId>mysql-connector-java</artifactId>
    <version>8.0.28</version>
</dependency>


For Gradle, add this line to your `build.gradle`:


implementation 'mysql:mysql-connector-java:8.0.28'