import java.sql.*;
import spark.ModelAndView;
import spark.template.handlebars.HandlebarsTemplateEngine;
import static spark.Spark.*;

public class Main {
    private static final String USER_NAME = "root";
    private static final String PASSWORD = "password";
    private static final String CONN_STR = "jdbc:mysql://localhost:3306/webdev";

    public static void main(String[] args) {
        get("/", (req, res) -> {
            Connection conn = DriverManager.getConnection(CONN_STR, USER_NAME, PASSWORD);
            Statement stmt = conn.createStatement();
            ResultSet rs = stmt.executeQuery("SELECT * FROM messages");
            String out = "";
            while (rs.next()) {
                out += "From: " + rs.getString(1) + "<br>Message: " + rs.getString(2);
            }
            return out;
        }, new HandlebarsTemplateEngine());
        post("/post", (req, res) -> {
            String name = req.queryParams("name");
            String message = req.queryParams("message");
            Connection conn = DriverManager.getConnection(CONN_STR, USER_NAME, PASSWORD);
            Statement stmt = conn.createStatement();
            stmt.executeUpdate("INSERT INTO messages VALUES ('" + name + "', '" + message + "')");
            return null;
        });
    }
}