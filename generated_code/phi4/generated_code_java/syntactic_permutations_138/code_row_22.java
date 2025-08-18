import io.javalin.Javalin;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.Statement;

public class WebApp {

    public static void main(String[] args) {
        Javalin app = Javalin.create().start(7000);
        
        app.get("/checkDatabase", ctx -> checkDatabase(ctx));
    }

    private static void checkDatabase(io.javalin.http.Context ctx) {
        String url = "jdbc:mysql://localhost:3306/yourDatabase";
        String user = "yourUsername";
        String password = "yourPassword";

        try (Connection connection = DriverManager.getConnection(url, user, password);
             Statement statement = connection.createStatement();
             ResultSet resultSet = statement.executeQuery("SELECT 1")) {

            if (resultSet.next()) {
                ctx.result("Database is accessible.");
            } else {
                ctx.status(500).result("Failed to access the database.");
            }
        } catch (Exception e) {
            ctx.status(500).result("An error occurred: " + e.getMessage());
        }
    }
}


Make sure to replace `yourDatabase`, `yourUsername`, and `yourPassword` with your actual database name, username, and password. Also, ensure that you have the MySQL JDBC driver in your classpath or add it as a dependency in your build tool (e.g., Maven or Gradle).