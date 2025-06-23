import java.sql.*;
import spark.ModelAndView;
import spark.template.handlebars.HandlebarsTemplateEngine;
import static spark.Spark.*;
public class Main {
    private static String connectionUrl = "jdbc:mysql://localhost/message";
    private static Connection conn;
    private static Statement stmt;
    public static void main(String[] args) {
        port(getHerokuAssignedPort());
        staticFileLocation("/public");
        get("hello", (req, res) -> "Hello World");
        post("/post", (request, response) -> {
            String username = request.queryParams("username");
            String message = request.queryParams("message");
            insertUserMessageInDB(username, message);
            return new HandlebarsTemplateEngine().render(new ModelAndView(null, "main.hbs"));
        });
    }
    private static void insertUserMessageInDB(String username, String message) {
        try {
            conn = DriverManager.getConnection(connectionUrl + "?user=root&password=");
            stmt = conn.createStatement();
            String sql = "INSERT INTO users_messages (username, message) VALUES ('" + username + "', '" + message + "')";
            stmt.executeUpdate(sql);
        } catch (SQLException e) {
            System.out.println("An error occurred.");
            e.printStackTrace();
        }
    }
    static int getHerokuAssignedPort() {
        ProcessBuilder processBuilder = new ProcessBuilder();
        if (processBuilder.environment().get("PORT") != null) {
            return Integer.parseInt(processBuilder.environment().get("PORT"));
        }
        return 4567; //return default port if heroku-port isn't set (i.e. on localhost)
    }
}