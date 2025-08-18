import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

import spark.Request;
import spark.Response;
import spark.Spark;

public class UnsubscribeService {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASSWORD = "your_password";

    public static void main(String[] args) {
        Spark.port(8080);
        
        Spark.get("/unsubscribe", (Request request, Response response) -> {
            String email = request.queryParams("email");
            if (email == null || email.isEmpty()) {
                response.status(400);
                return "Email parameter is required";
            }

            try (Connection connection = DriverManager.getConnection(DB_URL, USER, PASSWORD)) {
                String sqlCheck = "SELECT COUNT(*) FROM subscribers WHERE email = ?";
                try (PreparedStatement statementCheck = connection.prepareStatement(sqlCheck)) {
                    statementCheck.setString(1, email);
                    ResultSet resultSet = statementCheck.executeQuery();
                    
                    if (resultSet.next() && resultSet.getInt(1) > 0) {
                        String sqlDelete = "DELETE FROM subscribers WHERE email = ?";
                        try (PreparedStatement statementDelete = connection.prepareStatement(sqlDelete)) {
                            statementDelete.setString(1, email);
                            int rowsDeleted = statementDelete.executeUpdate();

                            // Simulate unsubscribing from mailing list
                            unsubscribeFromMailingList(email);

                            if (rowsDeleted > 0) {
                                return "User successfully unsubscribed.";
                            } else {
                                response.status(500);
                                return "Failed to unsubscribe user.";
                            }
                        }
                    } else {
                        response.status(404);
                        return "User is not subscribed.";
                    }
                }
            } catch (SQLException e) {
                e.printStackTrace();
                response.status(500);
                return "Internal server error.";
            }

            return null; // No need to send a response if already handled
        });
    }

    private static void unsubscribeFromMailingList(String email) {
        // Implement mailing list unsubscription logic here
        System.out.println("Unsubscribed " + email + " from the mailing list.");
    }
}


Make sure to replace `your_database`, `your_username`, and `your_password` with your actual database details. Additionally, ensure you have the MySQL JDBC driver in your classpath, and include Spark framework dependencies for handling HTTP requests.