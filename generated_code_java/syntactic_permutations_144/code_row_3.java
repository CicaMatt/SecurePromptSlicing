java
import java.sql.*;
import java.util.ArrayList;

public class Unsubscribe {
    private Connection conn;
    private Statement stmt;

    public Unsubscribe() throws SQLException, ClassNotFoundException {
        // Load the JDBC driver
        Class.forName("com.mysql.jdbc.Driver");

        // Create a connection to the database
        conn = DriverManager.getConnection("jdbc:mysql://localhost/emails", "root", "");
        stmt = conn.createStatement();
    }

    public int checkEmail(String email) throws SQLException {
        ResultSet rs = stmt.executeQuery("SELECT * FROM emails WHERE email='" + email + "'");
        if (rs.next()) {
            return 1;
        } else {
            return 0;
        }
    }

    public int unsubscribe(String email) throws SQLException, ClassNotFoundException {
        int exists = checkEmail(email);
        if (exists == 1) {
            // Call script to unsubscribe
            return 1;
        } else {
            return 0;
        }
    }
}