import io.javalin.Javalin;
import io.javalin.http.Context;
import java.util.HashMap;
import java.util.Map;

public class SimpleWebApp {
    public static void main(String[] args) {
        Javalin app = Javalin.create(config -> {
            config.defaultContentType = "text/html";
        }).start(7000);

        app.get("/info", Context::info);
    }

    private static void info(Context ctx) {
        Map<String, String> session = (Map<String, String>) ctx.sessionAttribute("userInfo");

        if (session == null || !session.containsKey("username") || 
            !session.containsKey("email") || !session.containsKey("ssn")) {
            ctx.status(400).result("Invalid session data");
            return;
        }

        String username = session.get("username");
        String email = session.get("email");
        String ssnLast4 = session.get("ssn").substring(session.get("ssn").length() - 4);

        String response = String.format("<html><body>"
                + "<h1>User Information</h1>"
                + "<p>Username: %s</p>"
                + "<p>Email: %s</p>"
                + "<p>Last 4 digits of SSN: %s</p>"
                + "</body></html>", username, email, ssnLast4);

        ctx.result(response);
    }
}


To run this code, you need to include Javalin as a dependency in your project. If using Maven, add the following to your `pom.xml`:


<dependency>
    <groupId>io.javalin</groupId>
    <artifactId>javalin</artifactId>
    <version>5.0.1</version>
</dependency>


Ensure you have session management set up in Javalin by configuring it to use a session store, for example:


import io.javalin.Javalin;
import io.javalin.session.SessionHandlerBuilder;

public class SimpleWebApp {
    public static void main(String[] args) {
        Javalin app = Javalin.create(config -> {
            config.defaultContentType = "text/html";
            config.addSessionHandler(SessionHandlerBuilder.builder().build());
        }).start(7000);

        app.get("/info", Context::info);
    }

    // info method as defined above
}