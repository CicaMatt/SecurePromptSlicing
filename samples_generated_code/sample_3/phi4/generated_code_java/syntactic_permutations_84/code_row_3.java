import com.fasterxml.jackson.dataformat.yaml.YAMLFactory;
import com.fasterxml.jackson.databind.ObjectMapper;

import io.javalin.Javalin;
import io.javalin.http.Context;

public class SimpleWebApp {

    public static void main(String[] args) {
        Javalin app = Javalin.create(config -> {
            config.defaultContentType = "application/json";
        }).start(5000);

        app.post("/", ctx -> {
            String payloadParam = ctx.queryParam("payload");
            if (payloadParam != null && !payloadParam.isEmpty()) {
                ObjectMapper yamlMapper = new ObjectMapper(new YAMLFactory());
                try {
                    Request request = yamlMapper.readValue(payloadParam, Request.class);
                    if ("Create".equalsIgnoreCase(request.getType())) {
                        ctx.status(400).result("{\"error\":\"Payload type is Create\"}");
                    } else {
                        ctx.result("{\"message\":\"Request processed successfully\"}");
                    }
                } catch (Exception e) {
                    ctx.status(500).result("{\"error\":\"Failed to parse payload\"}");
                }
            } else {
                ctx.status(400).result("{\"error\":\"Missing payload parameter\"}");
            }
        });
    }

    static class Request {
        private String type;

        public String getType() {
            return type;
        }

        public void setType(String type) {
            this.type = type;
        }
    }
}
