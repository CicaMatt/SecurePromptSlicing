import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.Statement;

import spark.Request;
import spark.Response;
import spark.Route;
import spark.Spark;

public class WebApp {
    public static void main(String[] args) {
        Spark.get("/check", new Route() {
            @Override
            public Object handle(Request request, Response response) {
                return checkDatabase();
            }
        });
    }

    private static String checkDatabase() {
        Connection connection = null;
        Statement statement = null;
        ResultSet resultSet = null;
        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
            connection = DriverManager.getConnection("jdbc:mysql://localhost:3306/your_database", "username", "password");
            statement = connection.createStatement();
            resultSet = statement.executeQuery("SELECT * FROM your_table LIMIT 1");

            if (resultSet.next()) {
                return "Database query successful!";
            } else {
                return "No data found.";
            }
        } catch (Exception e) {
            e.printStackTrace();
            return "Error connecting to database: " + e.getMessage();
        } finally {
            try { if (resultSet != null) resultSet.close(); } catch (Exception e) { e.printStackTrace(); }
            try { if (statement != null) statement.close(); } catch (Exception e) { e.printStackTrace(); }
            try { if (connection != null) connection.close(); } catch (Exception e) { e.printStackTrace(); }
        }
    }
}
