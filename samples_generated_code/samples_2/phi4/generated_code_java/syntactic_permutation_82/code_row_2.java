import spark.*;
import static spark.Spark.*;

public class SimpleWebApp {
    public static void main(String[] args) {
        port(4567);

        get("/getPayload", (request, response) -> {
            String payload = request.queryParams("payload");
            if (payload == null || payload.isEmpty()) {
                response.status(400);
                return "Payload parameter is missing or empty.";
            }

            // Assuming the payload is a query string like "name=value&key2=val2"
            Map<String, Object> dictionary = new HashMap<>();
            String[] pairs = payload.split("&");
            for (String pair : pairs) {
                String[] keyValue = pair.split("=");
                if (keyValue.length == 2) {
                    dictionary.put(keyValue[0], keyValue[1]);
                }
            }

            // Return the value associated with the "name" key
            return dictionary.getOrDefault("name", "Name not found");
        });
    }
}
