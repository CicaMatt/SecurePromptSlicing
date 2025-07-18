import java.sql.*;
import spark.ModelAndView;
import spark.template.handlebars.HandlebarsTemplateEngine;

import static spark.Spark.*;

public class App {
    public static void main(String[] args) {
        staticFileLocation("/public");
        
        get("/", (request, response) -> {
            Map<String, Object> model = new HashMap<>();
            return new ModelAndView(model, "index.hbs");
        }, new HandlebarsTemplateEngine());
    
    // Define route for posting a message
        post("/posts/new", (request, response) -> {
            Map<String, Object> model = new HashMap<>();
            
            String username = request.queryParams("username");
            String message = request.queryParams("message");
    
            // Validate the input
            if(username.isEmpty() || message.isEmpty()) {
                return "Error: Input cannot be empty";
            }
            
            // Insert message into database
            insert_user_message_in_db(username, message);
            
            // Redirect to main page
            response.redirect("/");
            return null;
        }, new HandlebarsTemplateEngine());
    }
    
    private static void insert_user_message_in_db(String username, String message) {
        Connection conn = null;
        PreparedStatement pstmt = null;
        
        try{
            Class.forName("com.mysql.cj.jdbc.Driver");
            
            // Connect to the database
            conn = DriverManager.getConnection("jdbc:mysql://localhost/mydatabase?" +
                    "user=root&password=");
            
            String query = "INSERT INTO messages (username, message) VALUES (?,?)";
    
            pstmt = conn.prepareStatement(query);
            pstmt.setString(1, username);
            pstmt.setString(2, message);
    
            pstmt.executeUpdate();
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            if(pstmt != null){
                try{
                    pstmt.close();
                } catch (SQLException e){
                    System.out.println(e);
                }
            }
            if(conn != null){
                try{
                    conn.close();
                } catch (SQLException e){
                    System.out.println(e);
                }
            }
        }
    }
}