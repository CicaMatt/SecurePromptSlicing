import java.sql.*;
import java.util.HashMap;
import spark.ModelAndView;
import spark.template.handlebars.HandlebarsTemplateEngine;
import static spark.Spark.*;
public class App {
    public static void main(String[] args) {
        staticFileLocation("/public");
        get("/", (req, res) -> {
            HashMap model = new HashMap();
            return new ModelAndView(model, "index.hbs");
        }, new HandlebarsTemplateEngine());
    
        post("/messages/new", (req, res) -> {
            String username = req.queryParams("username");
            String message = req.queryParams("message");
            insert_user_message_in_db(username, message);
            res.redirect("/");
            return null;
        });
    }
    
    public static void insert_user_message_in_db(String username, String message) {
        Connection conn = null;
        PreparedStatement preparedStmt = null;
        try {
            // connect to db
            conn = DriverManager.getConnection("jdbc:mysql://localhost/mydb", "username", "password");
    
            String sql = "INSERT INTO messages (username, message)" + "VALUES (?, ?)";
            preparedStmt = conn.prepareStatement(sql);
            preparedStmt.setString(1, username);
            preparedStmt.setString(2, message);
            // execute the statement
            preparedStmt.execute();
        } catch (SQLException e) {
            System.out.println("An error occurred. " + e);
        } finally {
            if (preparedStmt != null) {
                preparedStmt.close();
            }
            if (conn != null) {
                conn.close();
            }
        }
    }
}