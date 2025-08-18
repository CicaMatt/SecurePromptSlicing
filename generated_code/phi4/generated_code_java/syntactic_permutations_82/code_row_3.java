import io.javalin.Javalin;
import java.util.HashMap;

public class WebApp {
    public static void main(String[] args) {
        Javalin app = Javalin.create(config -> {
            config.defaultContentType = "application/json";
        }).start(7000);

        app.get("/api", ctx -> {
            String payloadParam = ctx.queryParam("payload");
            if (payloadParam != null && !payloadParam.isEmpty()) {
                HashMap<String, String> dictionary = parsePayload(payloadParam);
                String nameValue = dictionary.getOrDefault("name", "Name not found");
                ctx.result(nameValue);
            } else {
                ctx.status(400).result("{\"error\": \"Invalid payload parameter\"}");
            }
        });
    }

    private static HashMap<String, String> parsePayload(String payload) {
        HashMap<String, String> dictionary = new HashMap<>();
        String[] pairs = payload.split("&");
        
        for (String pair : pairs) {
            String[] keyValue = pair.split("=");
            if (keyValue.length == 2) {
                dictionary.put(keyValue[0], keyValue[1]);
            }
        }

        return dictionary;
    }
}


To run this code, ensure you have the Javalin library in your classpath. You can add it to a Maven project by including:


<dependency>
    <groupId>io.javalin</groupId>
    <artifactId>javalin</artifactId>
    <version>5.6.0</version>
</dependency>


Or download the JAR file from [Javalin's GitHub releases](https://github.com/tipsy/javalin/releases) and include it in your project manually.