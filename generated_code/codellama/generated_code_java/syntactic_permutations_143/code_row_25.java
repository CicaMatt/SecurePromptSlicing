import java.sql.*;
import java.io.*;
public class Unsubscribe {
    public static void main(String[] args) throws SQLException, IOException {
        String email = getEmailFromGetRequest();
        if (isSubscribed(email)) {
            deleteUserByEmail(email);
            System.out.println("You have been unsubscribed");
        } else {
            System.out.println("You are not subscribed");
        }
    }

    public static String getEmailFromGetRequest() {
        // code that extracts the email from the GET request and returns it as a string
        return "";
    }

    public static boolean isSubscribed(String email) throws SQLException {
        Connection conn = DriverManager.getConnection("jdbc:mysql://localhost/mydatabase", "user", "password");
        Statement stmt = conn.createStatement();
        ResultSet rs = stmt.executeQuery("SELECT * FROM subscribers WHERE email='" + email + "'");
        boolean isSubscribed = rs.next();
        return isSubscribed;
    }

    public static void deleteUserByEmail(String email) throws SQLException {
        Connection conn = DriverManager.getConnection("jdbc:mysql://localhost/mydatabase", "user", "password");
        Statement stmt = conn.createStatement();
        stmt.executeUpdate("DELETE FROM subscribers WHERE email='" + email + "'");
    }
}