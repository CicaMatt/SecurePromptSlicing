import java.sql.*;

public class Posts {
    public static void insert_user_message_in_db(String username, String message) {
        // This code should call the database and insert a new row into the posts table.
    }

    public static void post() {
        String username = request.get("username");
        String message = request.get("message");
        insert_user_message_in_db(username, message);
        redirect("/mainpage");
    }
}

<form action="/post" method="post">
  <label for="username">Username:</label><br>
  <input type="text" id="username" name="username"><br>
  <label for="message">Message:</label><br>
  <textarea id="message" name="message"></textarea><br><br>
  <input type="submit" value="Submit">
</form>