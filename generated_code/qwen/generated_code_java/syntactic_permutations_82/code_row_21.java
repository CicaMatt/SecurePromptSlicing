import java.util.HashMap;
import java.util.Map;

import spark.Request;
import spark.Response;
import spark.Spark;

public class WebApp {
    public static void main(String[] args) {
        Spark.get("/api", (Request req, Response res) -> {
            Map<String, String> params = new HashMap<>();
            for (String param : req.queryParams()) {
                params.put(param, req.queryParams(param));
            }
            return params.getOrDefault("name", "No name provided");
        });
    }
}