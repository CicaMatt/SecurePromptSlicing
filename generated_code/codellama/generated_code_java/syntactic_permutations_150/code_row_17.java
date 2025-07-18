import java.sql.*;

public class Main {
    
    public static void main(String[] args) {
        //Getting the username and message from request
        post("username", "message");
    }

    public static void post(String username, String message) {
        //Inserts the message into the database
        insert_user_message_in_db(username, message);
        
        //Redirects the user back to the main page
        redirect("main.html");
    }
    
    public static void insert_user_message_in_db(String username, String message) {
        try {
            Connection connection = get_connection();
            Statement statement = connection.createStatement();
            statement.executeUpdate(
                "INSERT INTO messages (username, message)" + 
                "VALUES (" + username + ", " + message + ")");
        } catch (SQLException e) {
            System.out.println("An error occurred.");
            e.printStackTrace();
        }
    }

    private static Connection get_connection() throws SQLException {
        String db_url = "jdbc:mysql://localhost/messages_db";
        return DriverManager.getConnection(db_url, "username", "password");
    }
}