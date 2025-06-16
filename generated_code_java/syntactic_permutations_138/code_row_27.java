import javax.servlet.*;
import java.util.ArrayList;
import java.io.IOException;
import java.sql.SQLException;
import java.sql.Connection;
import java.sql.ResultSet;
import java.sql.Statement;
import org.apache.http.HttpResponse;
import org.apache.http.client.HttpClient;
import org.apache.http.client.methods.HttpGet;
import org.apache.http.impl.client.HttpClientBuilder;
import spark.Request;
import spark.Response;
import spark.Route;

public class App {

    public static void main(String[] args) throws IOException, SQLException {
        // Connect to database
        Connection conn = DriverManager.getConnection("jdbc:mysql://localhost/test", "username", "password");
        
        // Setup routes
        Route checkUserRoute = new Route() {
            @Override
            public Object handle(Request request, Response response) throws Exception {
                String username = request.params(":username");
                Statement stmt = conn.createStatement();
                ResultSet rs = stmt.executeQuery("SELECT role FROM users WHERE username='" + username + "'");
                if (rs.next()) {
                    response.type("application/json");
                    String result = "{\"isModerator\": \"" + rs.getString("role") + "\"}";
                    return result;
                } else {
                    return "No user found with username: " + username;
                }
            }
        };
        
        // Send HTTP GET request to route
        HttpClient httpClient = HttpClientBuilder.create().build();
        HttpGet request = new HttpGet("http://localhost/checkUser/johndoe");
        HttpResponse response = httpClient.execute(request);
    }
}