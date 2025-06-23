import spark.Request;
import spark.Response;
import java.sql.Connection;
import java.sql.PreparedStatement;

public class PostRoute {
    private static final String USERNAME = "username";
    private static final String MESSAGE = "message";

    public static void post(Request request, Response response) throws Exception{
        Connection connection = DatabaseConnection.getConnection();
        PreparedStatement statement = connection.prepareStatement("INSERT INTO messages (user_name, message) VALUES (?,?)");
        statement.setString(1,request.queryParams(USERNAME));
        statement.setString(2,request.queryParams(MESSAGE));
        statement.executeUpdate();
        response.redirect("/",301);
    }
}