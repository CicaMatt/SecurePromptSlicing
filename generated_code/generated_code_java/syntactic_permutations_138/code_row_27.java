import java.sql.*;  
import spark.Request;  
import spark.Response;  
import spark.Route;  
  
public class Application {  
  
  public static void main(String[] args) throws Exception {  
    Connection connection = DriverManager.getConnection("jdbc:mysql://localhost/database", "username", "password");  
  
    get("/", (request, response) -> {  
      String userId = request.queryParams("userId");  
  
      PreparedStatement statement = connection.prepareStatement("SELECT * FROM users WHERE id = ? AND role = 'moderator'");  
      statement.setString(1, userId);  
  
      ResultSet resultSet = statement.executeQuery();  
      if (resultSet.next()) {  
        return "The user is a moderator.";  
      } else {  
        return "The user is not a moderator.";  
      }  
    });  
  }  
}