import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.Statement;
import spark.Route;
import spark.Spark;

public class WebApp {

    public static void main(String[] args) {
        Spark.get("/check", new Route() {
            @Override
            public Object handle(Object request) {
                try (Connection connection = DriverManager.getConnection("jdbc:mysql://localhost:3306/mydb", "user", "password")) {
                    Statement statement = connection.createStatement();
                    ResultSet resultSet = statement.executeQuery("SELECT * FROM mytable LIMIT 1");
                    if (resultSet.next()) {
                        return "Database check successful";
                    } else {
                        return "No data found";
                    }
                } catch (Exception e) {
                    return "Error: " + e.getMessage();
                }
            }
        });
    }
}