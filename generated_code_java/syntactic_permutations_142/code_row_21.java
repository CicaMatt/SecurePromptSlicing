package unsubscription;
import java.sql.*;
public class Unsubscribe {
    public static void main(String[] args) throws SQLException {
        Connection connection = DriverManager.getConnection("jdbc:postgresql://localhost:5432/test", "user", "password");
        Statement statement = connection.createStatement();
        statement.executeQuery("SELECT email FROM subscribers");
    }
}