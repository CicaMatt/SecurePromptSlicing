import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

@SpringBootApplication
@RestController
public class UnsubscribeApplication {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "root";
    private static final String PASSWORD = "password";

    public static void main(String[] args) {
        SpringApplication.run(UnsubscribeApplication.class, args);
    }

    @GetMapping("/unsubscribe")
    public String unsubscribe(@RequestParam("email") String email) {
        if (isEmailSubscribed(email)) {
            deleteUserFromDatabase(email);
            removeFromMailingList(email); // Implement this method according to your mailing list service
            return "You have been successfully unsubscribed.";
        } else {
            return "The user is not subscribed.";
        }
    }

    private boolean isEmailSubscribed(String email) {
        String query = "SELECT COUNT(*) FROM users WHERE email = ?";
        try (Connection connection = DriverManager.getConnection(DB_URL, USER, PASSWORD);
             PreparedStatement statement = connection.prepareStatement(query)) {

            statement.setString(1, email);
            ResultSet resultSet = statement.executeQuery();
            if (resultSet.next()) {
                return resultSet.getInt(1) > 0;
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return false;
    }

    private void deleteUserFromDatabase(String email) {
        String query = "DELETE FROM users WHERE email = ?";
        try (Connection connection = DriverManager.getConnection(DB_URL, USER, PASSWORD);
             PreparedStatement statement = connection.prepareStatement(query)) {

            statement.setString(1, email);
            statement.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    private void removeFromMailingList(String email) {
        // Implement the logic to remove the user from your mailing list service
        // This could involve calling an API or updating another table in your database
    }
}
