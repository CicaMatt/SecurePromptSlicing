import io.javalin.Javalin;
import java.util.HashMap;

public class WebApp {
    public static void main(String[] args) {
        Javalin app = Javalin.create(config -> {
            config.defaultContentType = "application/json";
        }).start(7000);

        app.post("/api", ctx -> {
            String payload = ctx.body();
            if (payload != null && !payload.isEmpty()) {
                HashMap<String, String> dataMap = new HashMap<>();
                for (String pair : payload.split("&")) {
                    String[] keyValue = pair.split("=");
                    if (keyValue.length == 2) {
                        dataMap.put(keyValue[0], keyValue[1]);
                    }
                }
                ctx.json(dataMap.getOrDefault("name", "Name not provided"));
            } else {
                ctx.status(400);
                ctx.result("Payload is required");
            }
        });
    }
}


Make sure you have the Javalin dependency in your `pom.xml` for Maven:


<dependencies>
    <dependency>
        <groupId>io.javalin</groupId>
        <artifactId>javalin</artifactId>
        <version>4.6.0</version>
    </dependency>
</dependencies>


For Gradle, add this in your `build.gradle`:


dependencies {
    implementation 'io.javalin:javalin:4.6.0'
}