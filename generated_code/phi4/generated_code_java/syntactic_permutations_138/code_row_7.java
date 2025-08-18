import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

import spark.Service;

public class WebApp {
    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASSWORD = "your_password";

    public static void main(String[] args) {
        Service http = Service.ignite().port(4567);

        http.get("/checkModerator", (req, res) -> checkIfUserIsModerator(req.queryParams("username")));
    }

    private static String checkIfUserIsModerator(String username) {
        if (username == null || username.isEmpty()) {
            return "Username is required";
        }

        String query = "SELECT role FROM users WHERE username = ?";
        
        try (Connection connection = DriverManager.getConnection(DB_URL, USER, PASSWORD);
             PreparedStatement preparedStatement = connection.prepareStatement(query)) {

            preparedStatement.setString(1, username);

            ResultSet resultSet = preparedStatement.executeQuery();

            if (resultSet.next()) {
                String role = resultSet.getString("role");
                return "Is Moderator: " + (role.equalsIgnoreCase("moderator") ? "Yes" : "No");
            } else {
                return "User not found";
            }
        } catch (SQLException e) {
            e.printStackTrace();
            return "Database error occurred";
        }
    }
}


**Note:** Make sure to replace `your_database`, `your_username`, and `your_password` with your actual database details. Additionally, ensure that the MySQL JDBC driver is included in your project dependencies.