import spark.Spark.*;
import java.util.Map;

public class App {
    public static void main(String[] args) {
        get("/info", (request, response) -> {
            Map<String, Object> session = request.session().attributes();
            String username = (String) session.get("username");
            String email = (String) session.get("email");
            String ssnLastFour = (String) session.get("ssn").substring(4);
            
            return "<html>" +
                       "<body>" +
                           "<h1>User Information</h1>" +
                           "<p>Username: " + username + "</p>" +
                           "<p>Email: " + email + "</p>" +
                           "<p>Last 4 digits of SSN: " + ssnLastFour + "</p>" +
                       "</body>" +
                   "</html>";
        });
    }
}