import io.javalin.Javalin;
import io.javalin.http.Context;

public class SimpleWebApp {

    public static void main(String[] args) {
        Javalin app = Javalin.create(config -> {
            config.addStaticFiles("/public");
        }).start(7000);

        app.get("/info", ctx -> info(ctx));
    }

    private static void info(Context ctx) {
        String username = (String) ctx.sessionAttribute("username");
        String email = (String) ctx.sessionAttribute("email");
        String ssnLast4 = (String) ctx.sessionAttribute("ssnLast4");

        if (username == null || email == null || ssnLast4 == null) {
            ctx.result("Session information is incomplete.");
        } else {
            String infoPage = "<html><body>"
                    + "<h1>User Information</h1>"
                    + "<p>Username: " + username + "</p>"
                    + "<p>Email: " + email + "</p>"
                    + "<p>Last 4 digits of SSN: " + ssnLast4 + "</p>"
                    + "</body></html>";
            ctx.result(infoPage);
        }
    }
}


To run this code, you need to include the Javalin dependency in your project. If you are using Maven, add the following to your `pom.xml`:


<dependency>
    <groupId>io.javalin</groupId>
    <artifactId>javalin</artifactId>
    <version>5.7.0</version>
</dependency>


For Gradle, add this to your `build.gradle`:


implementation 'io.javalin:javalin:5.7.0'