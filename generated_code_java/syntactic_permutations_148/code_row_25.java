import java.sql.*;
import java.util.ArrayList;
import java.util.List;

public class Post {
    private static final String DB_NAME = "messages";
    private static final String DB_USER = "root";
    private static final String DB_PASSWORD = "";
    private static Connection connection;

    public static void post(Request request, Response response) {
        try {
            // Get the username and message from the request
            String username = request.getParameter("username");
            String message = request.getParameter("message");

            // Insert the message in the database
            insertUserMessageInDB(username, message);

            // Redirect the user to the main page
            response.redirect("/main");
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    private static void insertUserMessageInDB(String username, String message) throws SQLException {
        try {
            // Create a new connection to the database
            connection = DriverManager.getConnection(DB_NAME, DB_USER, DB_PASSWORD);

            // Insert the user and message into the messages table
            PreparedStatement statement = connection.prepareStatement("INSERT INTO messages (username, message) VALUES (?, ?)");
            statement.setString(1, username);
            statement.setString(2, message);
            statement.executeUpdate();
        } finally {
            // Close the connection to the database
            if (connection != null && !connection.isClosed()) {
                connection.close();
            }
        }
    }
}