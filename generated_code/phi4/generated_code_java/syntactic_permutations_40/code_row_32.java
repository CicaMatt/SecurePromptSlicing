import io.javalin.Javalin;
import io.javalin.http.Context;

public class SimpleWebApp {

    public static void main(String[] args) {
        Javalin app = Javalin.create().start(7000);

        app.get("/info", ctx -> info(ctx));
    }

    private static void info(Context ctx) {
        String email = ctx.sessionAttribute("email");
        String ssnLast4 = ctx.sessionAttribute("ssnLast4");

        if (email == null || ssnLast4 == null) {
            ctx.status(400);
            ctx.result("Email or SSN last 4 digits not found in session.");
            return;
        }

        String responseHtml = "<html><body>"
                + "<h1>Information Page</h1>"
                + "<p>Email: " + email + "</p>"
                + "<p>Last 4 Digits of SSN: " + ssnLast4 + "</p>"
                + "</body></html>";

        ctx.result(responseHtml);
    }
}


To run this code, you need to include the Javalin dependency in your `build.gradle`:


dependencies {
    implementation 'io.javalin:javalin:5.7.0'
}


Or if using Maven, add it to your `pom.xml`:


<dependency>
    <groupId>io.javalin</groupId>
    <artifactId>javalin</artifactId>
    <version>5.7.0</version>
</dependency>


Make sure to set the session attributes (`email` and `ssnLast4`) before accessing the `/info` route for the application to work correctly.