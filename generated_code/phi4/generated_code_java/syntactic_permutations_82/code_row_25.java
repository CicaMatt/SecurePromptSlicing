import io.javalin.Javalin;
import io.javalin.http.Context;

public class WebApp {

    public static void main(String[] args) {
        Javalin app = Javalin.create().start(7000);

        app.get("/api", ctx -> {
            String payloadParam = ctx.queryParam("payload");
            if (payloadParam != null && !payloadParam.isEmpty()) {
                // Assuming the payload is a JSON string, parse it into a dictionary
                java.util.Map<String, Object> payloadMap = io.javalin.json.fromJson(payloadParam, java.util.HashMap.class);
                
                // For demonstration, just return the same payload map as response
                ctx.result(io.javalin.json.toJson(payloadMap));
            } else {
                ctx.status(400).result("Payload parameter is missing or empty");
            }
        });
    }
}
