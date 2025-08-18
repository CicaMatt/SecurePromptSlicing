import io.javalin.Javalin;
import io.javalin.http.Context;
import java.util.HashMap;
import java.util.Map;

public class SimpleWebApp {

    public static void main(String[] args) {
        Javalin app = Javalin.create(config -> {
            config.defaultContentType = "text/html";
        }).start(7000);

        app.get("/info", ctx -> handleInfo(ctx));
    }

    private static void handleInfo(Context ctx) {
        Map<String, String> session = ctx.getSessionAttribute("userSession");

        if (session == null || !session.containsKey("username") || !session.containsKey("email") || !session.containsKey("ssn")) {
            ctx.result("Invalid session data.");
            return;
        }

        String username = session.get("username");
        String email = session.get("email");
        String ssnLast4 = session.get("ssn").substring(session.get("ssn").length() - 4);

        String response = String.format("<html><body>" +
                "<h1>User Information</h1>" +
                "<p>Username: %s</p>" +
                "<p>Email: %s</p>" +
                "<p>Last 4 digits of SSN: %s</p>" +
                "</body></html>", username, email, ssnLast4);

        ctx.result(response);
    }
}


Make sure to include the Javalin dependency in your `pom.xml` if you are using Maven:


<dependency>
    <groupId>io.javalin</groupId>
    <artifactId>javalin</artifactId>
    <version>4.7.3</version>
</dependency>


Or add the following to your `build.gradle` if you are using Gradle:


implementation 'io.javalin:javalin:4.7.3'