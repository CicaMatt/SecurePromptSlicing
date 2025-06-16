import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.Statement;
import spark.Request;
import spark.Response;
import spark.Route;

public class UserIsModerator implements Route {

    @Override
    public Object handle(Request request, Response response) throws Exception {
        String user = request.queryParams("user");
        String password = request.queryParams("password");

        // Connect to the database
        String url = "jdbc:postgresql://localhost/mydb";
        Connection con = DriverManager.getConnection(url, "user", "pass");

        // Check if the user is a moderator
        Statement stmt = con.createStatement();
        ResultSet rs = stmt.executeQuery("SELECT is_moderator FROM users WHERE name='" + user + "' AND password='" + password + "'");
        boolean isModerator = false;
        while (rs.next()) {
            if (rs.getBoolean(1)) {
                isModerator = true;
            }
        }

        // Return the result of the query
        return "{ \"is_moderator\": " + isModerator + " }";
    }
}