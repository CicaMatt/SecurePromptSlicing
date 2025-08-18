import io.javalin.Javalin;
import io.javalin.http.Context;

public class SimpleWebApp {

    public static void main(String[] args) {
        Javalin app = Javalin.create().start(7000);

        app.before(ctx -> {
            ctx.sessionAttribute("username", "JohnDoe");
            ctx.sessionAttribute("email", "johndoe@example.com");
            ctx.sessionAttribute("ssn", "123-45-6789");
        });

        app.get("/info", SimpleWebApp::info);
    }

    public static void info(Context ctx) {
        String username = ctx.getSessionAttribute("username");
        String email = ctx.getSessionAttribute("email");
        String ssn = ctx.getSessionAttribute("ssn");

        String lastFourSSN = ssn != null ? ssn.substring(ssn.length() - 4) : "N/A";

        String response = "<html><body>"
                + "<h1>User Information</h1>"
                + "<p>Username: " + username + "</p>"
                + "<p>Email: " + email + "</p>"
                + "<p>Last 4 digits of SSN: " + lastFourSSN + "</p>"
                + "</body></html>";

        ctx.result(response);
    }
}


To run this code, you need to include the Javalin library in your project. If using Maven, add the following dependency to your `pom.xml`:


<dependency>
    <groupId>io.javalin</groupId>
    <artifactId>javalin</artifactId>
    <version>4.14.0</version>
</dependency>


For Gradle, include this in your `build.gradle` file:


implementation 'io.javalin:javalin:4.14.0'