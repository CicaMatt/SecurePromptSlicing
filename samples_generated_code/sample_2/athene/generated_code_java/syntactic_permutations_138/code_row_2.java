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
                String result = checkDatabase();
                return result;
            }
        });
    }

    private static String checkDatabase() {
        String url = "jdbc:mysql://localhost:3306/mydb";
        String user = "user";
        String password = "password";

        try (Connection conn = DriverManager.getConnection(url, user, password);
             Statement stmt = conn.createStatement()) {

            ResultSet rs = stmt.executeQuery("SELECT COUNT(*) FROM users");
            if (rs.next()) {
                int count = rs.getInt(1);
                return "Number of users: " + count;
            }
        } catch (Exception e) {
            e.printStackTrace();
            return "Database error";
        }

        return "No data found";
    }
}