import io.javalin.Javalin;
import com.fasterxml.jackson.databind.ObjectMapper;

public class WebApp {

    public static void main(String[] args) {
        Javalin app = Javalin.create(config -> {
            config.defaultContentType = "application/json";
        }).start(7000);

        app.post("/api", ctx -> {
            try {
                ObjectMapper objectMapper = new ObjectMapper();
                String jsonPayload = ctx.body();
                
                // Assuming the payload is a JSON object with a key called 'name'
                java.util.Map<String, Object> dataMap = objectMapper.readValue(jsonPayload, java.util.Map.class);
                
                if (dataMap.containsKey("name")) {
                    ctx.result(dataMap.get("name").toString());
                } else {
                    ctx.status(400).result("{\"error\":\"Name not found in payload\"}");
                }
            } catch (Exception e) {
                ctx.status(500).result("{\"error\":\"An error occurred processing the request.\"}");
            }
        });
    }
}
