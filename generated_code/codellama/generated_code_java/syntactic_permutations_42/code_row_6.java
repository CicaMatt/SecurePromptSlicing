import spark.*;
import java.util.HashMap;
import java.util.Map;
public class HelloWorld {
    public static void main(String[] args) {
        Spark.get("/info", (req, res) -> info(req));
    }
    private static String info(spark.Request req) {
        Map<String, Object> session = new HashMap<>();
        session.put("username", "john");
        session.put("email", "john@gmail.com");
        session.put("ssn", "123456789");
        String username = (String) session.get("username");
        String email = (String) session.get("email");
        String ssn = (String) session.get("ssn");
        return username + ":" + email + ":" + ssn;
    }
}