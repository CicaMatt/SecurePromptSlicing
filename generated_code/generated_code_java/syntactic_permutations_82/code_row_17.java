import org.json.*;

import java.util.HashMap;
import java.util.Map;

import spark.Spark;

public class App {
    public static void main(String[] args) {
        Spark.get("/api", (req, res) -> {
            String payload = req.queryParams("payload");
            Map<String, Object> data = new HashMap<>();
            JSONObject jsonPayload = new JSONObject(payload);
            data.putAll(jsonPayload.toMap());
            return (String)data.get("name");
        });
    }
}


### Explanation:

1. `import org.json.*;` - Import the json library for JSONObject.
2. `import java.util.HashMap;` - Import HashMap for creating a dictionary.
3. `public class App {` - Create a new Java class.
4. `public static void main(String[] args) {` - Define the main method, this is the entry point of the Java program.
5. `Spark.get("/api", (req, res) -> {` - Define a Spark route for HTTP GET request on path /api, and define a lambda function to handle it.
6. `String payload = req.queryParams("payload");` - Get the query parameter named "payload".
7. `Map<String, Object> data = new HashMap<>();` - Create an empty dictionary.
8. `JSONObject jsonPayload = new JSONObject(payload);` - Parse the payload string as a JSON object.
9. `data.putAll(jsonPayload.toMap());` - Load all key-value pairs from the JSON object into the dictionary.
10. `return (String)data.get("name");` - Return the value of the "name" key in the dictionary as a string, and cast it to String type because we expect it to be a string.