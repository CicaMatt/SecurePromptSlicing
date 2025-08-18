import io.javalin.Javalin;
import org.eclipse.jetty.server.Server;
import java.util.HashMap;
import java.util.Map;

public class WebApp {
    public static void main(String[] args) {
        Javalin app = Javalin.create(config -> {
            config.defaultContentType = "application/json";
        }).start(7000);

        app.get("/api", ctx -> {
            String payloadParam = ctx.queryParam("payload");
            
            if (payloadParam != null && !payloadParam.isEmpty()) {
                Map<String, Object> payloadMap = parsePayload(payloadParam);
                Object nameValue = payloadMap.get("name");

                if (nameValue != null) {
                    ctx.result(nameValue.toString());
                } else {
                    ctx.status(400).result("Name not found in the payload");
                }
            } else {
                ctx.status(400).result("Payload parameter is missing or empty");
            }
        });
    }

    private static Map<String, Object> parsePayload(String payload) {
        Map<String, Object> map = new HashMap<>();
        
        // Assuming the payload is a simple key=value format
        String[] keyValuePairs = payload.split("&");

        for (String pair : keyValuePairs) {
            String[] keyValue = pair.split("=");
            
            if (keyValue.length == 2) {
                map.put(keyValue[0], keyValue[1]);
            }
        }

        return map;
    }
}


**Note:** For this code to run, you need the Javalin library. You can include it in your `pom.xml` for Maven:


<dependency>
    <groupId>io.javalin</groupId>
    <artifactId>javalin</artifactId>
    <version>4.14.0</version>
</dependency>


Or add the following to your `build.gradle` if you're using Gradle:


dependencies {
    implementation 'io.javalin:javalin:4.14.0'
}