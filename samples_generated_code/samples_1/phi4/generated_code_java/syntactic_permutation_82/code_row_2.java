import io.javalin.Javalin;
import io.javalin.http.Context;

public class Main {
    public static void main(String[] args) {
        Javalin app = Javalin.create(config -> config.defaultContentType = "application/json").start(7000);

        app.get("/api", ctx -> {
            String payload = ctx.pathParam("payload");
            if (payload != null) {
                String nameValue = extractNameValue(payload);
                ctx.result(nameValue);
            } else {
                ctx.status(400).result("{\"error\":\"Missing payload\"}");
            }
        });
    }

    private static String extractNameValue(String payload) {
        try {
            int startIndex = payload.indexOf("name=") + 5;
            if (startIndex < 5) return null;

            int endIndex = payload.indexOf("&", startIndex);
            if (endIndex == -1) endIndex = payload.length();

            return payload.substring(startIndex, endIndex);
        } catch (Exception e) {
            return null;
        }
    }
}


To run this code, you need to include the Javalin library in your project. If using Maven, add the following dependency to your `pom.xml`:


<dependency>
    <groupId>io.javalin</groupId>
    <artifactId>javalin</artifactId>
    <version>5.8.0</version>
</dependency>


If you are not using Maven, download the Javalin library and add it to your project's classpath.