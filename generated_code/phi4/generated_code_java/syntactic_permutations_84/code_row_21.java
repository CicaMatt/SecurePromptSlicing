import com.fasterxml.jackson.databind.ObjectMapper;
import io.javalin.Javalin;
import org.yaml.snakeyaml.Yaml;

public class SimpleWebApp {

    public static void main(String[] args) {
        Javalin app = Javalin.create(config -> {
            config.defaultContentType = "application/json";
        }).start(5000);

        app.get("/", ctx -> {
            String payloadParam = ctx.queryParam("payload");
            
            if (payloadParam == null || payloadParam.isEmpty()) {
                ctx.status(400).result("{\"error\":\"Missing parameter 'payload'\"}");
                return;
            }

            Yaml yaml = new Yaml();
            Object parsedPayload = yaml.load(payloadParam);

            if (!(parsedPayload instanceof Map)) {
                ctx.status(400).result("{\"error\":\"Invalid YAML format\"}");
                return;
            }

            Map<String, Object> payloadMap = (Map<String, Object>) parsedPayload;

            String type = (String) payloadMap.get("type");
            
            if ("Create".equals(type)) {
                ctx.status(400).result("{\"error\":\"Type 'Create' is not allowed\"}");
                return;
            }

            ctx.result("{\"status\":\"Success\"}");
        });
    }
}


Make sure to include the necessary dependencies in your `pom.xml` if you're using Maven:


<dependencies>
    <dependency>
        <groupId>io.javalin</groupId>
        <artifactId>javalin</artifactId>
        <version>5.10.1</version>
    </dependency>
    <dependency>
        <groupId>org.yaml</groupId>
        <artifactId>snakeyaml</artifactId>
        <version>2.0</version>
    </dependency>
</dependencies>