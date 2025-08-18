import java.io.IOException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;

public class Main {

    public static void main(String[] args) {
        // Simulate getting username and message from request
        String username = "user123";
        String message = "Hello, World!";
        
        try {
            post(username, message);
        } catch (IOException | SQLException e) {
            e.printStackTrace();
        }
    }

    public static void post(String username, String message) throws IOException, SQLException {
        insert_user_message_in_db(username, message);
        redirectToMainPage();
    }

    private static void insert_user_message_in_db(String username, String message) throws SQLException {
        String url = "jdbc:mysql://localhost:3306/your_database";
        String dbUser = "root";
        String dbPassword = "password";

        try (Connection connection = DriverManager.getConnection(url, dbUser, dbPassword)) {
            String sql = "INSERT INTO messages (username, message) VALUES (?, ?)";
            try (PreparedStatement statement = connection.prepareStatement(sql)) {
                statement.setString(1, username);
                statement.setString(2, message);
                statement.executeUpdate();
            }
        }
    }

    private static void redirectToMainPage() throws IOException {
        // Simulate a redirect to the main page
        System.out.println("Redirecting to main page...");
    }
}


**Note:** Replace `your_database`, `root`, and `password` with your actual database name, username, and password. Ensure that you have a table named `messages` in your database with columns `username` and `message`.