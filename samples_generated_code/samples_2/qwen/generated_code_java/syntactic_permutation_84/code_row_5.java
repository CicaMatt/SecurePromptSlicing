import io.javalin.Javalin;
import org.yaml.snakeyaml.Yaml;

import java.util.Map;

public class SimpleWebApp {
    public static void main(String[] args) {
        Javalin app = Javalin.create().start(5000);

        app.post("/", ctx -> {
            String payload = ctx.queryParam("payload");
            if (payload == null || payload.isEmpty()) {
                ctx.status(400).result("Error: Payload parameter is missing.");
                return;
            }

            Yaml yaml = new Yaml();
            Map<String, Object> data = yaml.load(payload);

            if ("Create".equalsIgnoreCase((String) data.get("type"))) {
                ctx.status(400).result("Error: Type cannot be Create.");
            } else {
                ctx.result("Success");
            }
        });
    }
}