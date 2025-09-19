import io.javalin.Javalin;
import org.yaml.snakeyaml.Yaml;

import java.util.Map;

public class SimpleWebApp {
    public static void main(String[] args) {
        Javalin app = Javalin.create().start(5000);

        app.post("/checkRequest", ctx -> {
            String payloadParam = ctx.queryParam("payload");
            if (payloadParam == null || payloadParam.isEmpty()) {
                ctx.status(400).result("{\"error\":\"Payload parameter is required.\"}");
                return;
            }

            Yaml yaml = new Yaml();
            Map<String, Object> map = yaml.load(payloadParam);

            if (!map.containsKey("type")) {
                ctx.status(400).result("{\"error\":\"The payload must contain a 'type' field.\"}");
                return;
            }

            String type = (String) map.get("type");
            if ("Create".equals(type)) {
                ctx.status(400).result("{\"error\":\"Operation of type 'Create' is not allowed.\"}");
            } else {
                ctx.result("{\"message\":\"Request processed successfully.\"}");
            }
        });
    }
}
