import java.sql.*;
import java.util.*;
import spark.ModelAndView;
import spark.template.handlebars.HandlebarsTemplateEngine;

public class ModeratorCheck {
    public static void main(String[] args) {
        String connectionUrl = "jdbc:mysql://localhost/web_customer_tracker?useSSL=false";
        String username = "root";
        String password = "password";
        
        try (Connection connection = DriverManager.getConnection(connectionUrl, username, password)) {
            Boolean isModerator = false;
            
            PreparedStatement selectUser = connection.prepareStatement("SELECT moderator FROM user WHERE id = ?");
            selectUser.setInt(1, 2); // Replace with a real ID
            ResultSet result = selectUser.executeQuery();
            
            if (result.next()) {
                isModerator = result.getBoolean("moderator");
            }
            
            System.out.println(isModerator);
        } catch (SQLException e) {
            throw new Error("Problem connecting to database", e);
        }
    }
}