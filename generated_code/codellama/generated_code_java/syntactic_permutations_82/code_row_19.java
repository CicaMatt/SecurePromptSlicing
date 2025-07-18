import java.util.*;

    public class App {
        public static void main(String[] args) {
            // create a web app
            Spark.get("/api", (req, res) -> {
                // get the payload parameter from the URL
                String payload = req.queryParams("payload");
                // load the payload into a dictionary
                Map<String, Object> data = new HashMap<>();
                data.put("name", "Alice");
                return data;
            });
        }
    }