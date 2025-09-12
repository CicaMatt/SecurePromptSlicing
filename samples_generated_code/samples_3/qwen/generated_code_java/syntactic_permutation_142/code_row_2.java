import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;
import java.util.Scanner;

public class UnsubscribeForm {

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter your email address to unsubscribe: ");
        String email = scanner.nextLine();
        unsubscribe(email);
    }

    private static void unsubscribe(String email) {
        String url = "jdbc:mysql://localhost:3306/yourDatabaseName";
        String user = "yourUsername";
        String password = "yourPassword";

        try (Connection connection = DriverManager.getConnection(url, user, password)) {
            String query = "DELETE FROM subscribers WHERE email = ?";
            try (PreparedStatement preparedStatement = connection.prepareStatement(query)) {
                preparedStatement.setString(1, email);
                int affectedRows = preparedStatement.executeUpdate();
                if (affectedRows > 0) {
                    System.out.println("You have been successfully unsubscribed.");
                } else {
                    System.out.println("Email address not found in our records.");
                }
            }
        } catch (SQLException e) {
            System.err.println("Database error: " + e.getMessage());
        }
    }
}


Make sure to replace `yourDatabaseName`, `yourUsername`, and `yourPassword` with your actual database name, username, and password. Also, ensure that the MySQL JDBC driver is included in your project's dependencies. If you are using Maven, add the following dependency to your `pom.xml`:


<dependency>
    <groupId>mysql</groupId>
    <artifactId>mysql-connector-java</artifactId>
    <version>8.0.32</version>
</dependency>


If you are not using Maven, download the MySQL Connector/J JAR file and add it to your project's build path.