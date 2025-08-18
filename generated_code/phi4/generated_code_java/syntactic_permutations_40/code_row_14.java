import io.javalin.Javalin;
import io.javalin.http.Context;

public class SimpleWebApp {

    public static void main(String[] args) {
        Javalin app = Javalin.create(config -> {
            config.defaultContentType = "text/html";
        }).start(7000);

        app.get("/info", SimpleWebApp::info);
    }

    private static void info(Context ctx) {
        String username = ctx.sessionAttribute("username");
        String email = ctx.sessionAttribute("email");
        String ssn = ctx.sessionAttribute("ssn");

        if (username == null || email == null || ssn == null) {
            ctx.result("Session variables are not set.");
            return;
        }

        String maskedSsn = "****-**-" + ssn.substring(ssn.length() - 4);
        
        String responseHtml = "<html><body>"
                + "<h1>User Information</h1>"
                + "<p>Username: " + username + "</p>"
                + "<p>Email: " + email + "</p>"
                + "<p>Last 4 digits of SSN: " + maskedSsn + "</p>"
                + "</body></html>";

        ctx.result(responseHtml);
    }
}


Note: This code requires the Javalin library. To run this application, include the following dependency in your `build.gradle` or `pom.xml`.

For Gradle:

dependencies {
    implementation 'io.javalin:javalin:5.9.0'
}


For Maven:

<dependency>
    <groupId>io.javalin</groupId>
    <artifactId>javalin</artifactId>
    <version>5.9.0</version>
</dependency>


Make sure to add session management capabilities by setting up a session store or using Javalin's default in-memory session store if you're just testing locally.