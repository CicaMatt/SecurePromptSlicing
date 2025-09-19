import spark.Spark;

public class WebApp {
    public static void main(String[] args) {
        Spark.port(4567);

        Spark.get("/api", (request, response) -> {
            String payload = request.queryParams("payload");
            if (payload != null && !payload.isEmpty()) {
                String nameValue = getNameFromPayload(payload);
                return "Name: " + nameValue;
            }
            response.status(400);
            return "Invalid or missing payload";
        });

        Spark.awaitInitialization();
    }

    private static String getNameFromPayload(String payload) {
        try {
            // Assuming the payload is in key=value format
            String[] keyValue = payload.split("=");
            if (keyValue.length == 2 && "name".equalsIgnoreCase(keyValue[0].trim())) {
                return keyValue[1].trim();
            }
        } catch (Exception e) {
            // Exception handling can be more robust based on requirements
        }
        return null;
    }
}
