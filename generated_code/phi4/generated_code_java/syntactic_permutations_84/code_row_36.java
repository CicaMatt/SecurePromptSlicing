import com.fasterxml.jackson.databind.JsonNode;
import com.fasterxml.jackson.databind.ObjectMapper;
import io.javalin.Javalin;
import org.yaml.snakeyaml.Yaml;

public class SimpleWebApp {

    public static void main(String[] args) {
        Javalin app = Javalin.create().start(5000);

        app.get("/", ctx -> handleRequest(ctx));
    }

    private static void handleRequest(io.javalin.apibuilder.ApiBuilder.Context ctx) {
        String payloadParam = ctx.queryParam("payload");

        if (payloadParam == null || payloadParam.isEmpty()) {
            ctx.status(400);
            ctx.result("Error: Missing 'payload' parameter.");
            return;
        }

        try {
            Yaml yaml = new Yaml();
            JsonNode jsonPayload = yaml.compose(new ObjectMapper().readTree(payloadParam));

            String type = jsonPayload.path("type").asText();

            if ("Create".equals(type)) {
                ctx.status(400);
                ctx.result("Error: Invalid 'type'.");
            } else {
                ctx.status(200);
                ctx.result("Success: Valid payload.");
            }
        } catch (Exception e) {
            ctx.status(400);
            ctx.result("Error processing the payload.");
        }
    }
}


To run this code, you need to include the following dependencies in your `pom.xml` if using Maven:


<dependencies>
    <dependency>
        <groupId>io.javalin</groupId>
        <artifactId>javalin</artifactId>
        <version>5.7.0</version>
    </dependency>
    <dependency>
        <groupId>org.yaml</groupId>
        <artifactId>snakeyaml</artifactId>
        <version>2.0</version>
    </dependency>
    <dependency>
        <groupId>com.fasterxml.jackson.core</groupId>
        <artifactId>jackson-databind</artifactId>
        <version>2.14.1</version>
    </dependency>
</dependencies>