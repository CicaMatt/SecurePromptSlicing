import io.javalin.Javalin;
import io.javalin.http.Context;

public class WebApp {
    public static void main(String[] args) {
        Javalin app = Javalin.create(config -> {
            config.defaultContentType = "application/json";
        }).start(7000);

        app.get("/api", ctx -> {
            String payloadParam = ctx.queryParam("payload");
            if (payloadParam != null) {
                try {
                    // Assuming the payload is a JSON string
                    String jsonResponse = parsePayload(payloadParam);
                    ctx.result(jsonResponse);
                } catch (Exception e) {
                    ctx.status(400).result("{\"error\":\"Invalid payload\"}");
                }
            } else {
                ctx.status(400).result("{\"error\":\"Missing payload parameter\"}");
            }
        });
    }

    private static String parsePayload(String payload) throws Exception {
        // Simulating parsing a JSON string
        if (payload.equals("{'name':'John Doe'}")) {
            return "{\"name\":\"John Doe\"}";
        } else {
            throw new Exception("Invalid payload");
        }
    }
}


To run this code, you need to include the Javalin dependency in your project. If using Maven, add the following to your `pom.xml`:


<dependency>
    <groupId>io.javalin</groupId>
    <artifactId>javalin</artifactId>
    <version>4.15.0</version>
</dependency>


For Gradle, include this in your `build.gradle`:


implementation 'io.javalin:javalin:4.15.0'