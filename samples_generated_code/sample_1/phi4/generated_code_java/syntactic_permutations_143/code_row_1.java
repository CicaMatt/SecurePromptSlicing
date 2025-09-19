import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

@RestController
public class UnsubscribeController {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "root";
    private static final String PASSWORD = "password";

    @GetMapping("/unsubscribe")
    public String unsubscribe(@RequestParam("email") String email) {
        try (Connection connection = DriverManager.getConnection(DB_URL, USER, PASSWORD)) {
            if (isUserSubscribed(connection, email)) {
                deleteUserFromDatabase(connection, email);
                removeUserFromMailingList(email);
                return "User unsubscribed successfully.";
            } else {
                return "User is not subscribed.";
            }
        } catch (SQLException e) {
            e.printStackTrace();
            return "An error occurred while processing the request.";
        }
    }

    private boolean isUserSubscribed(Connection connection, String email) throws SQLException {
        String query = "SELECT COUNT(*) FROM users WHERE email = ?";
        try (PreparedStatement preparedStatement = connection.prepareStatement(query)) {
            preparedStatement.setString(1, email);
            try (ResultSet resultSet = preparedStatement.executeQuery()) {
                if (resultSet.next()) {
                    return resultSet.getInt(1) > 0;
                }
            }
        }
        return false;
    }

    private void deleteUserFromDatabase(Connection connection, String email) throws SQLException {
        String query = "DELETE FROM users WHERE email = ?";
        try (PreparedStatement preparedStatement = connection.prepareStatement(query)) {
            preparedStatement.setString(1, email);
            preparedStatement.executeUpdate();
        }
    }

    private void removeUserFromMailingList(String email) {
        // Implement your mailing list removal logic here
        System.out.println("Removed " + email + " from the mailing list.");
    }
}