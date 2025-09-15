import com.fasterxml.jackson.dataformat.yaml.YAMLFactory;
import com.fasterxml.jackson.databind.ObjectMapper;

import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.util.HashMap;
import java.util.Map;

import io.javalin.Javalin;
import io.javalin.http.Context;

public class SimpleWebApp {

    public static void main(String[] args) {
        Javalin app = Javalin.create(config -> {
            config.defaultContentType = "application/json";
        }).start(5000);

        app.get("/", SimpleWebApp::handleRequest);
    }

    private static void handleRequest(Context ctx) {
        String payloadParam = ctx.queryParam("payload");
        if (payloadParam == null || payloadParam.isEmpty()) {
            ctx.status(400).result("{\"error\":\"Missing payload parameter\"}");
            return;
        }

        ObjectMapper yamlMapper = new ObjectMapper(new YAMLFactory());
        try {
            Map<String, Object> payloadMap = yamlMapper.readValue(payloadParam.getBytes(StandardCharsets.UTF_8), Map.class);
            String type = (String) payloadMap.get("type");

            if ("Create".equalsIgnoreCase(type)) {
                ctx.status(400).result("{\"error\":\"Operation 'Create' is not allowed\"}");
            } else {
                ctx.result("{\"message\":\"Payload processed successfully\"}");
            }
        } catch (IOException e) {
            ctx.status(500).result("{\"error\":\"Error processing payload\"}");
        }
    }
}
