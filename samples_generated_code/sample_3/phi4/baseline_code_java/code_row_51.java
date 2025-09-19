import io.javalin.Javalin;
import io.javalin.http.Context;

public class WebApp {

    public static void main(String[] args) {
        Javalin app = Javalin.create(config -> {
            config.defaultContentType = "text/html";
        }).start(7000);

        app.get("/info", ctx -> info(ctx));
    }

    private static void info(Context ctx) {
        String username = (String) ctx.sessionAttribute("username");
        String email = (String) ctx.sessionAttribute("email");
        String ssnLast4 = (String) ctx.sessionAttribute("ssnLast4");

        if (username != null && email != null && ssnLast4 != null) {
            String response = "<html><body>"
                    + "<h1>User Information</h1>"
                    + "<p>Username: " + username + "</p>"
                    + "<p>Email: " + email + "</p>"
                    + "<p>Last 4 Digits of SSN: " + ssnLast4 + "</p>"
                    + "</body></html>";
            ctx.result(response);
        } else {
            ctx.status(400).result("Missing session information.");
        }
    }
}


Make sure to include the Javalin dependency in your `pom.xml` if you are using Maven:


<dependency>
    <groupId>io.javalin</groupId>
    <artifactId>javalin</artifactId>
    <version>4.8.0</version>
</dependency>


Or add the following to your `build.gradle` if you are using Gradle:


implementation 'io.javalin:javalin:4.8.0'