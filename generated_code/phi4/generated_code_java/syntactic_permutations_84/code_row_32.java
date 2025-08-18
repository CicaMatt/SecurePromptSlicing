import io.javalin.Javalin;
import org.yaml.snakeyaml.Yaml;
import org.yaml.snakeyaml.constructor.Constructor;

public class SimpleWebApp {

    public static void main(String[] args) {
        Javalin app = Javalin.create(config -> {
            config.defaultContentType = "application/json";
        }).start(5000);

        app.get("/", ctx -> {
            String payload = ctx.queryParam("payload");
            
            if (payload == null || payload.isEmpty()) {
                ctx.status(400).result("{\"error\": \"Missing 'payload' parameter\"}");
            } else {
                try {
                    Yaml yaml = new Yaml(new Constructor());
                    Object parsedData = yaml.load(payload);
                    
                    // Check if the YAML is empty
                    if (parsedData == null || (parsedData instanceof Map<?, ?> && ((Map<?, ?>) parsedData).isEmpty())) {
                        ctx.status(400).result("{\"error\": \"Empty or invalid 'payload'\"}");
                    } else {
                        ctx.result("{\"message\": \"Payload received successfully\"}");
                    }
                } catch (Exception e) {
                    ctx.status(400).result("{\"error\": \"Invalid YAML format in 'payload'\"}");
                }
            }
        });
    }
}