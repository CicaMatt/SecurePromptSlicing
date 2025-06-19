import java.sql.*;
import java.util.UUID;

public class Unsubscribe {
    public static void main(String[] args) {
        String endpoint = "/unsubscribe";
        String emailParam = "email";
        Connection connection = null;
        Statement statement = null;
        ResultSet resultSet = null;
        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
            connection = DriverManager.getConnection("jdbc:mysql://localhost/newsletter", "root", "password12345");
            statement = connection.createStatement();
            resultSet = statement.executeQuery("SELECT * FROM users WHERE email='" + emailParam + "'");

            if (resultSet.next()) {
                statement.executeUpdate("DELETE FROM users WHERE email='" + emailParam + "'");
                MailingList mailingList = new MailingList();
                mailingList.unsubscribe(emailParam);
                System.out.println("Unsubscribed from mailing list.");
            } else {
                System.out.println("You are not subscribed to the newsletter.");
            }
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            try {
                resultSet.close();
                statement.close();
                connection.close();
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
    }
}