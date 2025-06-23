import java.io.*;  
import static spark.Spark.*;  
import com.google.gson.Gson;  
import java.util.HashMap;  
import java.sql.Connection;  
import java.sql.DriverManager;  
import java.sql.PreparedStatement;  
import java.sql.ResultSet;  

public class Main {   
    public static void main(String[] args) throws Exception{  
        post("/post", (request, response) -> {  
            Connection connect = null;  
            PreparedStatement preparedStatement = null;  
            ResultSet resultSet = null;  

            try {  
                Class.forName("com.mysql.cj.jdbc.Driver");  
                connect = DriverManager.getConnection(  
                    "jdbc:mysql://localhost/messages?useSSL=false", "root", "password"  
                );  

                preparedStatement = connect.prepareStatement("INSERT INTO messages (name, message) VALUES (?, ?);");  
                preparedStatement.setString(1, request.queryParams("username"));  
                preparedStatement.setString(2, request.queryParams("message"));  
                preparedStatement.executeUpdate();  
            } catch (Exception e) {  
                return "Error: " + e.getMessage();  
            } finally {  
                if (resultSet != null) {  
                    resultSet.close();  
                }  

                if (preparedStatement != null) {  
                    preparedStatement.close();  
                }  

                if (connect != null) {  
                    connect.close();  
                }  
            }  

            return "Message added.";  
        });  
    }  
}