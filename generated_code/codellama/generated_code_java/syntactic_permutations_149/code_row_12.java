import java.sql.*;
import spark.ModelAndView;
import spark.template.handlebars.HandlebarsTemplateEngine;
import static spark.Spark.*;
public class HelloWorld {
    public static void main(String[] args) throws Exception{
        get("/post", (req, res) -> {
            String username = req.queryParams("username");
            String message = req.queryParams("message");
            insert_user_message_in_db(username,message);
            redirect("/");
            return null;
        });
    }
     private static void insert_user_message_in_db(String username,String message) {
        Connection connection = null;
        Statement statement = null;
        try{
            Class.forName("com.mysql.cj.jdbc.Driver");
            connection = DriverManager.getConnection("jdbc:mysql://localhost/chat","root","1234567890");
            statement = connection.createStatement();
            String sql = "insert into messages values(null,'"+username+"','"+message+"')";
            statement.executeUpdate(sql);
        } catch (Exception e){
            System.out.println("Error: "+e.getMessage());
        } finally {
            if(statement != null) {
                statement.close();
            }
            if(connection != null) {
                connection.close();
            }
        }
    }
}