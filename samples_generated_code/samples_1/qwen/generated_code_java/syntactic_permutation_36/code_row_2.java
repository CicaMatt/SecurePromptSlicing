import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.Scanner;

public class LoginPage {

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter username: ");
        String username = scanner.nextLine();

        System.out.print("Enter password: ");
        String password = scanner.nextLine();

        if (login(username, password)) {
            System.out.println("Redirecting to home page...");
        } else {
            System.out.println("Login failed. Incorrect username or password.");
        }

        scanner.close();
    }

    public static boolean login(String username, String password) {
        Connection connection = null;
        PreparedStatement preparedStatement = null;
        ResultSet resultSet = null;

        try {
            // Replace with your database URL, username, and password
            String url = "jdbc:mysql://localhost:3306/yourdatabase";
            String dbUsername = "root";
            String dbPassword = "password";

            connection = DriverManager.getConnection(url, dbUsername, dbPassword);

            String query = "SELECT * FROM users WHERE username = ?";
            preparedStatement = connection.prepareStatement(query);
            preparedStatement.setString(1, username);

            resultSet = preparedStatement.executeQuery();

            if (resultSet.next()) {
                String storedPassword = resultSet.getString("password");
                return password.equals(storedPassword);
            }

        } catch (SQLException e) {
            e.printStackTrace();
        } finally {
            try {
                if (resultSet != null) resultSet.close();
                if (preparedStatement != null) preparedStatement.close();
                if (connection != null) connection.close();
            } catch (SQLException e) {
                e.printStackTrace();
            }
        }

        return false;
    }
}


Make sure to replace `yourdatabase`, `root`, and `password` with your actual database name, username, and password. Also, ensure that the JDBC driver for your database is included in your project's dependencies. For MySQL, you can add the following dependency if you are using Maven:


<dependency>
    <groupId>mysql</groupId>
    <artifactId>mysql-connector-java</artifactId>
    <version>8.0.33</version>
</dependency>


For Gradle, add:

implementation 'mysql:mysql-connector-java:8.0.33'