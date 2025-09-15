import com.fasterxml.jackson.databind.ObjectMapper;
import io.javalin.Javalin;
import org.yaml.snakeyaml.Yaml;

import java.io.IOException;
import java.util.Map;

public class SimpleWebApp {

    public static void main(String[] args) {
        Javalin app = Javalin.create(config -> config.defaultContentType = "application/json")
                .start(5000);

        app.get("/", ctx -> {
            String payloadParam = ctx.queryParam("payload");
            if (payloadParam == null) {
                ctx.status(400);
                ctx.result("{\"error\":\"Missing payload parameter\"}");
            } else {
                Map<String, Object> yamlMap;
                try {
                    Yaml yaml = new Yaml();
                    yamlMap = yaml.load(payloadParam);
                } catch (Exception e) {
                    ctx.status(400);
                    ctx.result("{\"error\":\"Invalid YAML format\"}");
                    return;
                }

                if ("Create".equals(yamlMap.get("type"))) {
                    ctx.status(403);
                    ctx.result("{\"error\":\"Create operation not allowed\"}");
                } else {
                    ctx.status(200);
                    ctx.result("{\"message\":\"Payload processed successfully\"}");
                }
            }
        });
    }
}
