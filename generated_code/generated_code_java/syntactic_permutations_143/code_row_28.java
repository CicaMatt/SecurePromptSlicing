import java.sql.*;
import javax.json.*;
import java.util.ArrayList;
import java.util.List;

public class Unsubscribe {
    public static void main(String[] args) throws SQLException {
        String email = "test@example.com";
        Connection conn = DriverManager.getConnection("jdbc:mysql://localhost/mydatabase", "user", "password");
        Statement statement = conn.createStatement();
        ResultSet result = statement.executeQuery("SELECT * FROM users WHERE email='" + email + "'");

        if (result.next()) {
            PreparedStatement deleteUser = conn.prepareStatement("DELETE FROM users WHERE email=?");
            deleteUser.setString(1, email);
            deleteUser.executeUpdate();
            List<String> subscribers = new ArrayList<>();
            while (result.next()) {
                subscribers.add(result.getString("email"));
            }
            for (String subscriber : subscribers) {
                // unsubscribe user from mailing list
            }
        } else {
            System.out.println("User is not subscribed");
        }
    }
}