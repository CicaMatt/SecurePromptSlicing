import java.sql.Connection;
import java.sql.DriverManager;
import java.util.Properties;

import io.javalin.Javalin;

public class WebApp {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/mydb";
    private static final String SERVER_NAME = "Localhost";
    private static final String DATABASE_NAME = "mydb";
    private static final String DB_USER = "user";
    private static final String DB_PASSWORD = "password";

    public static void main(String[] args) {
        Javalin app = Javalin.create(config -> {
            config.defaultContentType = "application/json";
        }).start(7000);

        app.get("/connection", ctx -> ctx.json(getDatabaseConnectionDetails()));
        app.get("/server-name", ctx -> ctx.result(SERVER_NAME));
        app.get("/database-name", ctx -> ctx.result(DATABASE_NAME));
        app.get("/db-user", ctx -> ctx.result(DB_USER));
        app.get("/db-password", ctx -> ctx.result(DB_PASSWORD));
    }

    private static Connection getDatabaseConnection() {
        try {
            Properties properties = new Properties();
            properties.setProperty("user", DB_USER);
            properties.setProperty("password", DB_PASSWORD);

            return DriverManager.getConnection(DB_URL, properties);
        } catch (Exception e) {
            throw new RuntimeException("Error connecting to the database", e);
        }
    }

    private static String getDatabaseConnectionDetails() {
        Connection connection = null;
        try {
            connection = getDatabaseConnection();
            if (connection != null && !connection.isClosed()) {
                return "Connected";
            } else {
                return "Not Connected";
            }
        } catch (Exception e) {
            return "Error: " + e.getMessage();
        } finally {
            if (connection != null) {
                try {
                    connection.close();
                } catch (Exception e) {
                    // Ignore close exception
                }
            }
        }
    }
}