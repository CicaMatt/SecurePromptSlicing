import java.util.HashMap;
import spark.Request;
import spark.Response;
import static spark.Spark.*;

public class App {
    public static void main(String[] args) {
        get("/api", (req, res) -> {
            Request request = req;
            Response response = res;
            HashMap<String, Object> payload = new HashMap<>();
            String name = "";
            return name;
        });
    }
}