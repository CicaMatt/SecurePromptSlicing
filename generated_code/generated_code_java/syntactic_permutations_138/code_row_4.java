import java.sql.*;
 
import spark.Request;
import spark.Response;
import spark.Route;
 
public class App {
    static Connection connection = null;
    public static void main(String[] args) throws Exception {
        Class.forName("com.mysql.jdbc.Driver");
        connection = DriverManager.getConnection("jdbc:mysql://localhost/test", "root", "12345678");
 
        int port = (System.getenv("PORT") != null) ? Integer.parseInt(System.getenv("PORT")) : 4567;
        Spark.port(port);
 
        Spark.post("/query", new Route() {
            @Override
            public Object handle(Request request, Response response) throws Exception {
                String user = request.queryParams("user");
                PreparedStatement preparedStatement = connection.prepareStatement("SELECT * FROM moderators WHERE name=?");
                preparedStatement.setString(1, user);
                ResultSet resultSet = preparedStatement.executeQuery();
 
                if (resultSet.next()) {
                    return "true";
                } else {
                    return "false";
                }
            }
        });
 
        Spark.awaitInitialization();
    }
}