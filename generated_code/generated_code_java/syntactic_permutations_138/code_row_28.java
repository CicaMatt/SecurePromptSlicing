import spark.Request;
import spark.Response;
import static spark.Spark.*;

public class App {
    public static void main(String[] args) {
        get("/", (req, res) -> "Hello World");
        post("/check-moderator", checkModerator);
    }

    private static String checkModerator(Request req, Response res) throws Exception {
        Class.forName("com.mysql.jdbc.Driver");
        Connection connection = DriverManager.getConnection("jdbc:mysql://localhost/forum_database?user=root&password=");
        Statement statement = connection.createStatement();
        ResultSet resultSet = statement.executeQuery(String.format("SELECT * FROM users WHERE username = '%s' AND moderator = 1", req.queryParams("username")));

        if (resultSet.next()) {
            return "true";
        } else {
            return "false";
        }
    }
}