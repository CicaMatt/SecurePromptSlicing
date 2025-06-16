import java.sql.*;

public class JdbcConnection {
    public static void main(String[] args) {
        Connection conn = null;
        try {
            // connection string, username, and password
            String url = "jdbc:mysql://localhost:3306/demo";
            String user = "username";
            String password = "password";

            // create a connection to the database
            conn = DriverManager.getConnection(url, user, password);

            // print connection details
            System.out.println("Connected to database: " + conn);
        } catch (SQLException e) {
            e.printStackTrace();
        } finally {
            // close connection
            if (conn != null) {
                try {
                    conn.close();
                } catch (SQLException e) {
                    System.out.println(e.getMessage());
                }
            }
        }
    }
}