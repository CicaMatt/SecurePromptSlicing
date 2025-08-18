import java.util.HashMap;
import java.util.Map;

import spark.Request;
import spark.Response;
import spark.Route;
import spark.Spark;

public class WebApp {
    public static void main(String[] args) {
        Spark.get("/api", new Route() {
            @Override
            public Object handle(Request request, Response response) {
                Map<String, String> params = new HashMap<>();
                for (String key : request.queryParams()) {
                    params.put(key, request.queryParams(key));
                }
                return params.getOrDefault("name", "No name provided");
            }
        });
    }
}