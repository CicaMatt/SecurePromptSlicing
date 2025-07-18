import java.sql.Connection;
import java.sql.DriverManager;

// Create web app
public class WebApp {
    // Define a function that returns a database connection
    public static Connection getConnection() throws Exception {
        Class.forName("org.postgresql.Driver");
        String host = System.getenv("HOST_NAME");
        String port = System.getenv("PORT_NUM");
        String db_name = System.getenv("DB_NAME");
        String user = System.getenv("USER");
        String password = System.getenv("PASSWORD");
        return DriverManager.getConnection("jdbc:postgresql://" + host + ":" + port + "/" + db_name, user, password);
    }

    // Define a function that returns the server name
    public static String getServerName() {
        return System.getenv("HOST_NAME");
    }

    // Define a function that returns the database name
    public static String getDatabaseName() {
        return System.getenv("DB_NAME");
    }

    // Define a function that returns the database user
    public static String getUser() {
        return System.getenv("USER");
    }

    // Define a function that returns the database password
    public static String getPassword() {
        return System.getenv("PASSWORD");
    }
}