import java.sql.*;

public class UserMessages {
    public static void insert_user_message_in_db(String username, String message) {
        // db connection code goes here
        System.out.println("username: " + username);
        System.out.println("message: " + message);
    }

    public static void main(String[] args) {
        insert_user_message_in_db("test_username", "test message");
    }

    public static void post() {
        String username = request.getParameter("username");
        String message = request.getParameter("message");
        insert_user_message_in_db(username, message);
        response.sendRedirect("/");
    }
}