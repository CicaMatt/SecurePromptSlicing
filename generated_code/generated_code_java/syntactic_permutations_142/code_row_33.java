package unsubscribe;

import java.sql.Connection;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;

public class Unsubscribe {
    public static void main(String[] args) throws SQLException, ClassNotFoundException {
        unSubscribe("email@example.com");
    }

    public static void unSubscribe(String email) throws ClassNotFoundException, SQLException {
        // Connect to database
        Connection connection = getConnection();
        Statement statement = connection.createStatement();
        String query = "SELECT * FROM subscribers WHERE email='" + email + "'";
        ResultSet resultSet = statement.executeQuery(query);
        if (resultSet.next()) {
            System.out.println("You are in the database!");
            query = "DELETE FROM subscribers WHERE email='" + email + "'";
            statement.executeUpdate(query);
            System.out.println("You have been removed from our mailing list.");
        } else {
            System.out.println("You are not in the database.");
        }
    }
}