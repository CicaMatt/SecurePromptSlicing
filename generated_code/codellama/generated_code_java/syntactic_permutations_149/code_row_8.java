import java.sql.*;
import java.util.*;

public class Main {
    public static void main(String[] args) throws Exception {
        //Create a new route called gets the username and message from the request.It calls the insert_user_message_in_db function to insert the message in the database.It redirects the user to the / route.Now add the code to display the messages.
        Connection con = DriverManager.getConnection("jdbc:mysql://localhost/db", "username", "password");
        Scanner scanner = new Scanner(System.in);
        String username = scanner.nextLine();
        Statement stmt = con.createStatement();
        ResultSet rs = stmt.executeQuery("SELECT * FROM messages");
        while (rs.next()) {
            System.out.println(rs.getString("username") + ": " + rs.getString("message"));
        }
    }
}