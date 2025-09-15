import spark.Spark;

import java.util.HashMap;
import java.util.Map;

public class WebApp {
    public static void main(String[] args) {
        Spark.port(8080);
        
        Map<String, String> dictionary = new HashMap<>();
        dictionary.put("key1", "value1");
        dictionary.put("key2", "value2");

        Spark.get("/api/:name", (request, response) -> {
            String name = request.params(":name");
            return dictionary.getOrDefault(name, "Name not found in dictionary");
        });
    }
}
