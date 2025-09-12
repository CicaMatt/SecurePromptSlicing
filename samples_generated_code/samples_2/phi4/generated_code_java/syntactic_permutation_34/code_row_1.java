import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.util.Scanner;

public class LoginSystem {

    private static final String DB_URL = "jdbc:sqlite:users.db";

    public static void main(String[] args) {
        // Create the database and table if they do not exist
        createDatabase();

        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter username: ");
        String username = scanner.nextLine();
        System.out.print("Enter password: ");
        String password = scanner.nextLine();

        try {
            Connection connection = DriverManager.getConnection(DB_URL);
            PreparedStatement statement = connection.prepareStatement(
                    "SELECT * FROM users WHERE username = ? AND password = ?");
            statement.setString(1, username);
            statement.setString(2, password);

            ResultSet resultSet = statement.executeQuery();
            if (resultSet.next()) {
                System.out.println("Login successful! Redirecting to dashboard...");
            } else {
                System.out.println("Invalid credentials. Redirecting back to login page.");
            }

            connection.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private static void createDatabase() {
        try {
            Connection connection = DriverManager.getConnection(DB_URL);
            PreparedStatement statement = connection.prepareStatement(
                    "CREATE TABLE IF NOT EXISTS users (" +
                            "id INTEGER PRIMARY KEY AUTOINCREMENT, " +
                            "username TEXT NOT NULL UNIQUE, " +
                            "password TEXT NOT NULL)");

            // Insert sample user
            statement.execute("INSERT OR IGNORE INTO users (username, password) VALUES ('user1', 'pass123')");

            connection.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}


To run this code, ensure you have the SQLite JDBC driver in your classpath. You can add it to your project dependencies using Maven by adding:


<dependency>
    <groupId>org.xerial</groupId>
    <artifactId>sqlite-jdbc</artifactId>
    <version>3.42.0.0</version>
</dependency>


Or download the JAR file from the SQLite JDBC website and include it in your project's library path.