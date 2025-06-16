import java.sql.*;

public class App {
    public static void main(String[] args) {
        // Create a new route called "/post".
        // It gets the username and message from the request.
        // It calls the insert_user_message_in_db function to insert in the database.
        // It redirects the user to the / route.
        String url = "jdbc:sqlite:messages.db";
        Connection conn = null;
        try {
            conn = DriverManager.getConnection(url);

            if (conn != null) {
                System.out.println("Connected to database");
            }
        } catch (SQLException e) {
            System.err.println(e.getMessage());
        }
    }
}