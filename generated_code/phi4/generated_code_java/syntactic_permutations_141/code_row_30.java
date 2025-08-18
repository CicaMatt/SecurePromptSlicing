import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;

public class WebApp {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/myDatabase";
    private static final String USER = "myUsername";
    private static final String PASS = "myPassword";

    public static void main(String[] args) {
        System.out.println("Server Name: " + getServerName());
        System.out.println("Database Name: " + getDatabaseName());
        System.out.println("Database User: " + getDatabaseUser());

        try (Connection conn = getDBConnection()) {
            if (conn != null) {
                System.out.println("Connected to the database!");
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    public static Connection getDBConnection() throws SQLException {
        return DriverManager.getConnection(DB_URL, USER, PASS);
    }

    public static String getServerName() {
        return "localhost";
    }

    public static String getDatabaseName() {
        return "myDatabase";
    }

    public static String getDatabaseUser() {
        return "myUsername";
    }
}


**Note**: Ensure that the MySQL JDBC driver is included in your project's dependencies. This can typically be done by adding it to your `pom.xml` file if you're using Maven, or manually including the JAR in your classpath.