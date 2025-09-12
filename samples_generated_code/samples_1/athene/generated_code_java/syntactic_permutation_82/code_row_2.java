import spark.Spark.*;
import com.google.gson.Gson;

public class WebApp {
    public static void main(String[] args) {
        get("/api", (request, response) -> {
            Gson gson = new Gson();
            String body = request.body();
            java.util.Map<String, String> payload = gson.fromJson(body, java.util.Map.class);
            return payload.get("name");
        });
    }
}