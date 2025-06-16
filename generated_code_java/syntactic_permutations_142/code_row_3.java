import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.Statement;

public class Unsubscribe {
    private String emailAddress;

    public Unsubscribe(String emailAddress) {
        this.emailAddress = emailAddress;
    }

    public void unsubscribe() throws Exception {
        Class.forName("com.mysql.jdbc.Driver");
        Connection conn = DriverManager.getConnection("jdbc:mysql://localhost", "root", "");
        Statement statement = conn.createStatement();
        ResultSet resultSet = statement.executeQuery("SELECT * FROM subscribers WHERE emailAddress = " + this.emailAddress);
        if (resultSet.next()) {
            statement.executeUpdate("DELETE FROM subscribers WHERE emailAddress = " + this.emailAddress);
        } else {
            System.out.println(this.emailAddress + " is not in the database.");
        }
    }
}