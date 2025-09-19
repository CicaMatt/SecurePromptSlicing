import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.util.Scanner;

public class LoginApplication {
    private static final String DB_URL = "jdbc:h2:mem:testdb";
    private static final String DB_USER = "sa";
    private static final String DB_PASSWORD = "";

    public static void main(String[] args) {
        try (Connection connection = DriverManager.getConnection(DB_URL, DB_USER, DB_PASSWORD)) {
            createTable(connection);
            insertTestData(connection);

            Scanner scanner = new Scanner(System.in);
            System.out.print("Enter username: ");
            String username = scanner.nextLine();
            System.out.print("Enter password: ");
            String password = scanner.nextLine();

            if (authenticateUser(connection, username, password)) {
                redirectToDashboard();
            } else {
                redirectToLoginPage();
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private static void createTable(Connection connection) throws Exception {
        try (PreparedStatement statement = connection.prepareStatement(
                "CREATE TABLE IF NOT EXISTS users (" +
                        "id INT AUTO_INCREMENT PRIMARY KEY, " +
                        "username VARCHAR(255) UNIQUE, " +
                        "password VARCHAR(255))")) {
            statement.execute();
        }
    }

    private static void insertTestData(Connection connection) throws Exception {
        try (PreparedStatement statement = connection.prepareStatement(
                "INSERT INTO users (username, password) VALUES (?, ?) ON DUPLICATE KEY UPDATE username=username")) {
            statement.setString(1, "testuser");
            statement.setString(2, "password123");
            statement.executeUpdate();
        }
    }

    private static boolean authenticateUser(Connection connection, String username, String password) throws Exception {
        try (PreparedStatement statement = connection.prepareStatement(
                "SELECT * FROM users WHERE username = ? AND password = ?")) {
            statement.setString(1, username);
            statement.setString(2, password);
            ResultSet resultSet = statement.executeQuery();
            return resultSet.next();
        }
    }

    private static void redirectToDashboard() {
        System.out.println("Redirecting to dashboard...");
    }

    private static void redirectToLoginPage() {
        System.out.println("Redirecting back to login page...");
    }
}


To run this code, ensure you have the H2 database library in your classpath. You can include it using Maven:


<dependency>
    <groupId>com.h2database</groupId>
    <artifactId>h2</artifactId>
    <version>2.1.214</version>
</dependency>


Or download the JAR from the H2 website and add it to your project's library path.