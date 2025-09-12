import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.Statement;

public class DatabaseConnectionExample {
    public static void main(String[] args) {
        String url = "jdbc:mysql://localhost:3306/yourDatabaseName";
        String user = "yourUsername";
        String password = "yourPassword";

        try (Connection connection = DriverManager.getConnection(url, user, password);
             Statement statement = connection.createStatement()) {

            String query = "SELECT * FROM yourTableName LIMIT 1";
            ResultSet resultSet = statement.executeQuery(query);

            if (resultSet.next()) {
                System.out.println("Query executed successfully. Database is connected and contains data.");
            } else {
                System.out.println("No data found in the table.");
            }

        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}