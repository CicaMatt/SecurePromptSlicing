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
