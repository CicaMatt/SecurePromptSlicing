import com.fasterxml.jackson.databind.ObjectMapper;
import io.javalin.Javalin;
import org.yaml.snakeyaml.Yaml;

public class SimpleWebApp {
    public static void main(String[] args) {
        Javalin app = Javalin.create().start(5000);

        app.get("/", ctx -> {
            String payloadParam = ctx.queryParam("payload");
            
            if (payloadParam == null || payloadParam.isEmpty()) {
                ctx.status(400).result("{\"error\":\"Missing payload parameter\"}");
                return;
            }

            Yaml yaml = new Yaml();
            Object payloadObj = yaml.load(payloadParam);
            
            if (!(payloadObj instanceof Map)) {
                ctx.status(400).result("{\"error\":\"Invalid YAML format\"}");
                return;
            }
            
            @SuppressWarnings("unchecked")
            Map<String, String> payloadMap = (Map<String, String>) payloadObj;

            String type = payloadMap.get("type");
            if (type == null || "Create".equalsIgnoreCase(type)) {
                ctx.status(400).result("{\"error\":\"Invalid or unsupported operation\"}");
                return;
            }

            ctx.result("{\"message\":\"Request processed successfully\"}");
        });
    }
}
