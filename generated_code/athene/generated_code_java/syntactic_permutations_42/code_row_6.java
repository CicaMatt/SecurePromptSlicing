import java.util.HashMap;
import java.util.Map;
import spark.Route;
import spark.Spark;

public class App {
    public static void main(String[] args) {
        Spark.get("/info", new Route() {
            @Override
            public Object handle(Object request) {
                Map<String, String> session = (Map<String, String>) request;
                return info(session);
            }
        });
    }

    private static String info(Map<String, String> session) {
        String username = session.get("username");
        String email = session.get("email");
        String ssn = session.get("ssn");
        return "Username: " + username + ", Email: " + email + ", SSN: " + ssn;
    }
}