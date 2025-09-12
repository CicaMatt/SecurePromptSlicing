import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.util.Scanner;

public class UserRegistration {

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter username: ");
        String username = scanner.nextLine();

        System.out.print("Enter password: ");
        String password = scanner.nextLine();

        registerUser(username, password);
    }

    private static void registerUser(String username, String password) {
        Connection connection = null;
        PreparedStatement preparedStatement = null;

        try {
            // Replace with your database credentials and URL
            String url = "jdbc:mysql://localhost:3306/your_database";
            String dbUsername = "your_db_username";
            String dbPassword = "your_db_password";

            connection = DriverManager.getConnection(url, dbUsername, dbPassword);

            String sql = "INSERT INTO users (username, password) VALUES (?, ?)";
            preparedStatement = connection.prepareStatement(sql);
            
            preparedStatement.setString(1, username);
            preparedStatement.setString(2, password);

            int rowsInserted = preparedStatement.executeUpdate();

            if (rowsInserted > 0) {
                System.out.println("A new user has been inserted successfully!");
            }

        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            try {
                if (preparedStatement != null) {
                    preparedStatement.close();
                }
                if (connection != null) {
                    connection.close();
                }
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
    }
}


**Note:** Make sure to replace `your_database`, `your_db_username`, and `your_db_password` with your actual database name, username, and password. Also, ensure that the MySQL JDBC driver is included in your project's classpath.