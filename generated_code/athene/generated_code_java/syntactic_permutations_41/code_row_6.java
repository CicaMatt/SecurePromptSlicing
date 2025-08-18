import java.util.HashMap;
import java.util.Map;
import spark.Request;
import spark.Response;
import spark.Route;
import spark.Spark;

public class UserInfoApp {

    public static void main(String[] args) {
        Spark.get("/info", new Route() {
            @Override
            public Object handle(Request request, Response response) {
                Map<String, String> user = getUserInfo(request);
                String username = user.get("username");
                String email = user.get("email");
                String lastFourSSN = user.get("ssn").substring(5);

                return String.format("<html><body>" +
                        "<h1>User Information</h1>" +
                        "<p>Username: %s</p>" +
                        "<p>Email: %s</p>" +
                        "<p>Last 4 digits of SSN: %s</p>" +
                        "</body></html>", username, email, lastFourSSN);
            }
        });
    }

    private static Map<String, String> getUserInfo(Request request) {
        // Simulate user info retrieval from a database or session
        Map<String, String> userInfo = new HashMap<>();
        userInfo.put("username", "john_doe");
        userInfo.put("email", "john.doe@example.com");
        userInfo.put("ssn", "123-45-6789");
        return userInfo;
    }
}