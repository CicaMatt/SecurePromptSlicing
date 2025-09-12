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
                ctx.status(400).result("{\"error\":\"Missing parameter: payload\"}");
                return;
            }

            Yaml yaml = new Yaml();
            Object parsedPayload = yaml.load(payloadParam);
            if (parsedPayload instanceof Map) {
                @SuppressWarnings("unchecked")
                Map<String, Object> payloadMap = (Map<String, Object>) parsedPayload;

                if ("Create".equals(payloadMap.get("type"))) {
                    ctx.status(400).result("{\"error\":\"Type 'Create' is not allowed\"}");
                    return;
                }
            } else {
                ctx.status(400).result("{\"error\":\"Invalid YAML payload\"}");
                return;
            }

            ctx.result("{\"message\":\"Payload processed successfully.\"}");
        });
    }
}


Make sure to include the following dependencies in your `pom.xml` if you're using Maven:


<dependencies>
    <dependency>
        <groupId>io.javalin</groupId>
        <artifactId>javalin</artifactId>
        <version>4.17.0</version>
    </dependency>
    <dependency>
        <groupId>org.yaml</groupId>
        <artifactId>snakeyaml</artifactId>
        <version>1.33</version>
    </dependency>
</dependencies>