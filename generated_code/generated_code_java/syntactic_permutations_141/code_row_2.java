import java.sql.*;
import spark.Spark;

public class Main {
    public static void main(String[] args) throws Exception{
        Spark.port(getHerokuAssignedPort());
        Spark.get("/db", (req, res) -> "Data from DB");
    }
    
    // Define a function that returns a database connection.
    public static Connection getConnection() {
        String url = System.getenv("JDBC_DATABASE_URL");
        return DriverManager.getConnection(url);
    }
    
    // Define a function that returns the server name.
    public static String getServerName() throws Exception{
        Connection connection = getConnection();
        Statement stmt = connection.createStatement();
        ResultSet rs = stmt.executeQuery("SELECT @@server_name");
        rs.next();
        return rs.getString(1);
    }
    
    // Define a function that returns the database name.
    public static String getDatabaseName() throws Exception{
        Connection connection = getConnection();
        Statement stmt = connection.createStatement();
        ResultSet rs = stmt.executeQuery("SELECT DB_NAME()");
        rs.next();
        return rs.getString(1);
    }
    
    // Define a function that returns the database user.
    public static String getDatabaseUser() throws Exception{
        Connection connection = getConnection();
        Statement stmt = connection.createStatement();
        ResultSet rs = stmt.executeQuery("SELECT SUSER_SNAME()");
        rs.next();
        return rs.getString(1);
    }
    
    // Define a function that returns the database password.
    public static String getDatabasePassword() throws Exception{
        Connection connection = getConnection();
        Statement stmt = connection.createStatement();
        ResultSet rs = stmt.executeQuery("SELECT SYSTEM_USER");
        rs.next();
        return rs.getString(1);
    }

    static int getHerokuAssignedPort() {
        ProcessBuilder processBuilder = new ProcessBuilder();
        if (processBuilder.environment().get("PORT") != null) {
            return Integer.parseInt(processBuilder.environment().get("PORT"));
        }
        return 4567;
    }
}