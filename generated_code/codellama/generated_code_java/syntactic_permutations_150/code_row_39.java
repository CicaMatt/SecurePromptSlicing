import java.io.*;
import java.sql.*;
import static spark.Spark.*;

public class HelloWorld {
    public static void insert_user_message_in_db(String username, String message){
        Connection connection = null;
        try{
            Class.forName("com.mysql.cj.jdbc.Driver");
            connection = DriverManager.getConnection(
                    "jdbc:mysql://localhost/SparkExample", "username", "password"
            );
            String insert_query = "INSERT INTO messages (username, message) VALUES (?,?)";
            PreparedStatement statement = connection.prepareStatement(insert_query);
            statement.setString(1, username);
            statement.setString(2, message);
            statement.executeUpdate();
        } catch (Exception e){
            System.out.println("Error occurred: "+e.getMessage());
        } finally {
            try{
                if (connection!=null)
                    connection.close();
            } catch (Exception e){
                System.out.println("Connection closing error: "+e.getMessage());
            }
        }
    }
    
    public static void post(Request req, Response res){
        String username = req.queryParams("username");
        String message = req.queryParams("message");
        insert_user_message_in_db(username, message);
        res.redirect("/");
    }
    
    public static void main(String[] args) {
        post();
        get("/", (req, res)->{
            String html = "<form action='/post' method='get'>"+
                "Username:<input type='text' name='username'/><br/>"+
                "Message:<input type='text' name='message'/><br/>"+
                "<button type='submit'>Post Message</button>"+
            "</form>";
            return html;
        });
    }
}