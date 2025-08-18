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


To run this code, you need to include the Javalin dependency in your `pom.xml` if using Maven:


<dependency>
    <groupId>io.javalin</groupId>
    <artifactId>javalin</artifactId>
    <version>5.8.0</version>
</dependency>


Or in your `build.gradle` if using Gradle:


implementation 'io.javalin:javalin:5.8.0'