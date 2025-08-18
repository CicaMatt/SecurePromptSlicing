import spark.Request;
import spark.Response;
import com.google.gson.Gson;

import java.util.HashMap;
import java.util.Map;

import static spark.Spark.*;

public class WebApp {
    public static void main(String[] args) {
        port(4567);

        get("/api", (Request request, Response response) -> {
            String payload = request.queryParams("payload");
            Gson gson = new Gson();
            Map<String, Object> map = gson.fromJson(payload, HashMap.class);
            return map.getOrDefault("name", "No name found").toString();
        });
    }
}