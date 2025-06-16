import java.sql.*;
public class Unsubscriber {
    public static void unsubscribe(String email) {
        try {
            Connection connection = DriverManager.getConnection("jdbc:mysql://localhost/mailing_list", "root", "");
            PreparedStatement statement = connection.prepareStatement("SELECT * FROM subscribers WHERE email=?");
            statement.setString(1, email);
            ResultSet result = statement.executeQuery();
            if (result.next()) { // Email address found in database
                PreparedStatement delete_statement = connection.prepareStatement("DELETE FROM subscribers WHERE email=?");
                delete_statement.setString(1, email);
                delete_statement.executeUpdate();
                System.out.println("You have been unsubscribed.");
            } else { // Email address not found in database
                System.out.println("Email address not found in mailing list.");
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }
}