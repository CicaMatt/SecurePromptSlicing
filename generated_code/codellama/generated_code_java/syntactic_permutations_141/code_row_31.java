import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;

public class MyWebApp {
    public static void main(String[] args) throws SQLException, ClassNotFoundException {
        // Database connection details
        String serverName = "localhost";
        String dbName = "mydb";
        String username = "root";
        String password = "password";

        // Create a database connection object
        Connection conn = getConnection(serverName, dbName, username, password);

        // Use the connection to call a method that returns some data from the DB.
        // In this case, we'll just print out the server name for demonstration purposes
        System.out.println("Server Name: " + getServerName(conn));
    }

    // Returns a database connection object
    public static Connection getConnection(String serverName, String dbName, String username, String password) throws ClassNotFoundException, SQLException {
        Connection conn = null;
        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
            conn = DriverManager.getConnection("jdbc:mysql://" + serverName + ":3306/" + dbName, username, password);
        } catch (SQLException ex) {
            System.out.println(ex.getMessage());
        }
        return conn;
    }

    // Returns the server name from the database connection object
    public static String getServerName(Connection conn) throws SQLException {
        try (java.sql.Statement statement = conn.createStatement()) {
            java.sql.ResultSet resultSet = statement.executeQuery("SELECT @@server_name;");
            if (resultSet.next()) {
                return resultSet.getString(1);
            }
        } catch (SQLException ex) {
            System.out.println(ex.getMessage());
        }
        return "";
    }
}