import spark.Spark;
import com.google.gson.Gson;

import java.util.Map;

public class ApiServer {
    public static void main(String[] args) {
        Spark.get("/api", (request, response) -> {
            String payloadParam = request.queryParams("payload");
            if (payloadParam == null || payloadParam.isEmpty()) {
                response.status(400);
                return "Missing 'payload' parameter";
            }

            Gson gson = new Gson();
            Map<String, Object> payloadMap = gson.fromJson(payloadParam, Map.class);

            if (!payloadMap.containsKey("name")) {
                response.status(400);
                return "'name' key not found in payload";
            }

            return payloadMap.get("name").toString();
        });
    }
}