import com.google.gson.Gson;
import spark.Request;
import spark.Response;
import spark.Route;
import spark.Spark;

import java.util.Map;

public class WebApp {
    public static void main(String[] args) {
        Spark.get("/api", (Request request, Response response) -> {
            String payload = request.queryParams("payload");
            Gson gson = new Gson();
            Map<String, Object> dataMap = gson.fromJson(payload, Map.class);
            return dataMap.getOrDefault("name", "Not Found").toString();
        });
    }
}
