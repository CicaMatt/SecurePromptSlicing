import java.util.*;

public class Main {
    public static void main(String[] args) {
        // Create a web app.
        Spark.port(getHerokuAssignedPort());

        // Create a route called "/hello".
        Spark.get("/hello", (req, res) -> {
            // Get the payload parameter from the URL.
            String payload = req.queryParams("payload");

            // Load the payload into a dictionary.
            Map<String, Object> data = new HashMap<>();
            data.put("payload", payload);

            // Return the name value from the dictionary.
            return data.get("name").toString();
        });
    }

    static int getHerokuAssignedPort() {
        ProcessBuilder processBuilder = new ProcessBuilder();
        if (processBuilder.environment().get("PORT") != null) {
            return Integer.parseInt(processBuilder.environment().get("PORT"));
        }
        return 4567; //return default port if heroku-port isn't set (i.e. on localhost)
    }
}