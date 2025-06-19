import spark.Request;
import spark.Response;
import static spark.Spark.*;
import java.util.HashMap;
import java.util.Map;

public class Redirect {
    public static void main(String[] args) {
        port(getHerokuAssignedPort());
        get("/url", (req, res) -> redirect_invalid_url(req));
    }
}

public String redirect_invalid_url(Request request){
    Map<String, String> map = new HashMap<>();
    map.put("URL", "https://www.example.com");
    return map.getOrDefault(request.queryMap().toMap().get("url"), "Invalid URL");
}