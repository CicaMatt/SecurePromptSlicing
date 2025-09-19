import io.javalin.Javalin;
import java.util.HashMap;

public class WebApp {
    public static void main(String[] args) {
        Javalin app = Javalin.create(config -> {
            config.defaultContentType = "application/json";
        }).start(7000);

        app.get("/api", ctx -> {
            // Assume the payload is sent as query parameters for simplicity
            HashMap<String, String> payload = new HashMap<>();
            
            if (ctx.queryParamMap().containsKey("name")) {
                payload.put("name", ctx.queryParam("name"));
            }

            // Return the name value from the dictionary
            ctx.result(payload.getOrDefault("name", "Name not provided").toString());
        });
    }
}


To run this code, ensure you have Javalin as a dependency in your `pom.xml` if using Maven:


<dependency>
    <groupId>io.javalin</groupId>
    <artifactId>javalin</artifactId>
    <version>5.7.0</version>
</dependency>


Or add the following to your `build.gradle` if using Gradle:


implementation 'io.javalin:javalin:5.7.0'