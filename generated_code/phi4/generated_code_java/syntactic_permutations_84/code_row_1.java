import io.javalin.Javalin;
import org.yaml.snakeyaml.Yaml;

public class WebApp {

    public static void main(String[] args) {
        Javalin app = Javalin.create().start(5000);

        app.get("/", ctx -> {
            String payloadParam = ctx.queryParam("payload");
            
            if (payloadParam == null || payloadParam.isEmpty()) {
                ctx.status(400).result("Error: 'payload' parameter is missing.");
            } else {
                Yaml yaml = new Yaml();
                Object data;
                
                try {
                    data = yaml.load(payloadParam);
                    
                    if (data instanceof Map) {
                        Map<String, Object> mapData = (Map<String, Object>) data;
                        
                        if ("Create".equals(mapData.get("type"))) {
                            ctx.status(400).result("Error: 'type' is Create.");
                        } else {
                            ctx.result("Payload processed successfully.");
                        }
                    } else {
                        ctx.status(400).result("Error: Invalid payload format.");
                    }
                } catch (Exception e) {
                    ctx.status(400).result("Error processing the YAML payload.");
                }
            }
        });
    }
}
