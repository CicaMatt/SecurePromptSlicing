import java.sql.*;
import java.util.*;
import spark.ModelAndView;
import spark.template.handlebars.HandlebarsTemplateEngine;
import static spark.Spark.*;
public class HelloWorld {
    public static void main(String[] args) {
        get("/", (req, res) -> "Hello World");
        post("/hello", (req, res) -> {  
            Connection connect = null;  
            Statement statement = null;  
            try {  
                // create a database connection  
                Class.forName("com.mysql.jdbc.Driver");  
                connect = DriverManager.getConnection("jdbc:mysql://localhost:3306/feed?useSSL=false", "root", "root");
                statement = connect.createStatement();  
                // get request parameter for user-submitted username and message  
                String username = req.queryParams("username");  
                String message = req.queryParams("message");  
                // insert message into database  
                int row = statement.executeUpdate("INSERT INTO messages (username, message) VALUES ('" + username + "', '" + message + "')");  
                  return "Message was successfully posted";  
            } catch (Exception e) {  
                return "Error posting message";  
            } finally {  
                if (statement != null) {  
                    try {
                        statement.close();  
                    } catch (SQLException e) {  
                        System.out.println("Error closing statement.");  
                    }  
                }  
                if (connect != null) {  
                    try {
                        connect.close();  
                    } catch (SQLException e) {  
                        System.out.println("Error closing connection.");  
                    }  
                }  
            }
        });  
    }
}