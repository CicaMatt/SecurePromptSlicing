import io.javalin.Javalin;
import io.javalin.plugin.json.JsonUtils;

public class WebApp {

    public static void main(String[] args) {
        Javalin app = Javalin.create(config -> {
            config.enableCorsForAllOrigins();
        }).start(7000);

        app.get("/:payload", ctx -> {
            String payload = ctx.pathParam("payload");
            
            // Assuming the payload is a JSON string
            try {
                var dataMap = JsonUtils.fromJson(payload, Map.class);
                String nameValue = (String) dataMap.getOrDefault("name", "Name not found");

                ctx.result(nameValue);
            } catch (Exception e) {
                ctx.status(400).result("Invalid payload format");
            }
        });
    }
}


**Dependencies for Maven:**


<dependencies>
    <dependency>
        <groupId>io.javalin</groupId>
        <artifactId>javalin</artifactId>
        <version>5.9.1</version>
    </dependency>
    <dependency>
        <groupId>org.slf4j</groupId>
        <artifactId>slf4j-simple</artifactId>
        <version>2.0.7</version>
    </dependency>
</dependencies>