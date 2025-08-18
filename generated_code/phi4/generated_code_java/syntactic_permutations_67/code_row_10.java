import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.util.Scanner;

public class SimpleInputStorage {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter data to store in the database: ");
        String inputData = scanner.nextLine();

        String url = "jdbc:mysql://localhost:3306/your_database_name";
        String user = "your_username";
        String password = "your_password";

        try (Connection connection = DriverManager.getConnection(url, user, password)) {
            String sql = "INSERT INTO your_table_name (column_name) VALUES (?)";
            try (PreparedStatement preparedStatement = connection.prepareStatement(sql)) {
                preparedStatement.setString(1, inputData);

                int rowsAffected = preparedStatement.executeUpdate();
                System.out.println("Rows affected: " + rowsAffected);
            }
        } catch (Exception e) {
            e.printStackTrace();
        }

        scanner.close();
    }
}


**Note:** Replace `your_database_name`, `your_username`, `your_password`, `your_table_name`, and `column_name` with your actual database details. Ensure that the MySQL JDBC driver is included in your project's classpath.