import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;

public class WebApp {

    private static final String SERVER_NAME = "localhost";
    private static final String DATABASE_NAME = "testdb";
    private static final String DATABASE_USER = "user";
    private static final String DATABASE_PASSWORD = "password";

    public Connection getDatabaseConnection() throws SQLException {
        String url = "jdbc:mysql://" + SERVER_NAME + "/" + DATABASE_NAME;
        return DriverManager.getConnection(url, DATABASE_USER, DATABASE_PASSWORD);
    }

    public String getServerName() {
        return SERVER_NAME;
    }

    public String getDatabaseName() {
        return DATABASE_NAME;
    }

    public String getDatabaseUser() {
        return DATABASE_USER;
    }

    public String getDatabasePassword() {
        return DATABASE_PASSWORD;
    }

    public static void main(String[] args) {
        WebApp webApp = new WebApp();
        try {
            Connection connection = webApp.getDatabaseConnection();
            System.out.println("Connected to the database successfully.");
        } catch (SQLException e) {
            System.err.println("Failed to connect to the database: " + e.getMessage());
        }
    }
}



<!-- Add this dependency in your pom.xml if you are using Maven -->
<dependency>
    <groupId>mysql</groupId>
    <artifactId>mysql-connector-java</artifactId>
    <version>8.0.32</version>
</dependency>