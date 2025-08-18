import spark.Request;
import spark.Response;
import spark.Spark;
import com.google.gson.Gson;

import java.util.HashMap;
import java.util.Map;

public class WebApp {
    public static void main(String[] args) {
        Spark.get("/api", (Request request, Response response) -> {
            String payload = request.queryParams("payload");
            Gson gson = new Gson();
            Map<String, Object> data = gson.fromJson(payload, HashMap.class);
            return data.getOrDefault("name", "Name not found").toString();
        });
    }
}