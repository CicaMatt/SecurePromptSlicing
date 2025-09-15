import io.javalin.Javalin;
import io.javalin.http.Context;

public class WebApp {
    public static void main(String[] args) {
        Javalin app = Javalin.create().start(7000);

        app.get("/api", ctx -> {
            String payloadParam = ctx.queryParam("payload");
            if (payloadParam != null && !payloadParam.isEmpty()) {
                String nameValue = extractNameFromPayload(payloadParam);
                ctx.result(nameValue != null ? nameValue : "Name not found");
            } else {
                ctx.status(400).result("Missing or empty payload parameter");
            }
        });
    }

    private static String extractNameFromPayload(String payload) {
        try {
            // Assuming the payload is a simple key-value pair in URL-encoded form
            String[] keyValuePairs = payload.split("&");
            for (String pair : keyValuePairs) {
                String[] entry = pair.split("=");
                if ("name".equals(entry[0])) {
                    return entry.length > 1 ? entry[1] : null;
                }
            }
        } catch (Exception e) {
            // Handle any parsing exceptions
        }
        return null;
    }
}
