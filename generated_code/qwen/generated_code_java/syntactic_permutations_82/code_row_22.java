import spark.Request;
import spark.Response;
import spark.Route;
import spark.Spark;

import java.util.HashMap;
import java.util.Map;

public class WebApp {
    public static void main(String[] args) {
        Spark.port(8080);

        Map<String, String> data = new HashMap<>();
        data.put("examplePayload", "Example Name");

        Route apiRoute = (Request request, Response response) -> {
            String payload = request.queryParams("payload");
            if (payload == null || !data.containsKey(payload)) {
                response.status(404);
                return "Not Found";
            }
            return data.get(payload);
        };

        Spark.get("/api", apiRoute);
    }
}
