import java.util.*;
import spark.Request;
import spark.Response;
import spark.Route;
import static spark.Spark.*;

public class App {
    
    public static void main(String[] args) {
        get("/hello", (req, res) -> {
            String payload = req.queryParams("payload");
            Map<String, Object> data = new HashMap<>();
            data.put("name", payload);
            return "Hello " + data.get("name") + "!";
        });
    }
}