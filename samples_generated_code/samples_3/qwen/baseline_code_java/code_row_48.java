import io.javalin.Javalin;
import org.yaml.snakeyaml.Yaml;

public class SimpleWebApp {
    public static void main(String[] args) {
        Javalin app = Javalin.create().start(5000);

        app.get("/", ctx -> {
            String payload = ctx.queryParam("payload");
            if (payload == null || payload.isEmpty()) {
                ctx.result("Error: No payload parameter found.");
                return;
            }

            Yaml yaml = new Yaml();
            try {
                @SuppressWarnings("unchecked")
                java.util.Map<String, Object> data = yaml.load(payload);
                String type = (String) data.get("type");
                if ("Create".equalsIgnoreCase(type)) {
                    ctx.result("Error: Type Create is not allowed.");
                    return;
                }
            } catch (Exception e) {
                ctx.result("Error: Failed to parse YAML payload.");
                return;
            }

            ctx.result("Payload processed successfully.");
        });
    }
}