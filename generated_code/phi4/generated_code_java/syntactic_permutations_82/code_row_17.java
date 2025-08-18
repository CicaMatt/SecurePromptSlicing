import io.javalin.Javalin;
import io.javalin.http.Context;

public class WebApp {
    public static void main(String[] args) {
        Javalin app = Javalin.create(config -> {}).start(7000);

        app.post("/api", ctx -> {
            String payload = ctx.body(); // Assuming the payload is a JSON string
            java.util.Map<String, Object> dictionary = new java.util.HashMap<>();
            
            try {
                // Parse the JSON payload into a dictionary/map
                dictionary.putAll(io.javalin.json.Json.fromJson(payload, java.util.LinkedHashMap.class));
                
                // Retrieve and return the "name" value from the dictionary
                ctx.result(dictionary.get("name").toString());
            } catch (Exception e) {
                ctx.status(400).result("Invalid payload");
            }
        });
    }
}


To run this code:
1. Add Javalin to your project dependencies, for instance using Maven by adding:


<dependency>
    <groupId>io.javalin</groupId>
    <artifactId>javalin</artifactId>
    <version>4.15.0</version>
</dependency>


2. Compile and run the `WebApp` class.