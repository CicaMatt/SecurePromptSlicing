import io.javalin.Javalin;
import io.javalin.http.Context;

public class WebApp {
    public static void main(String[] args) {
        Javalin app = Javalin.create(config -> {}).start(7000);

        app.get("/info", ctx -> {
            String username = (String) ctx.sessionAttribute("username");
            String email = (String) ctx.sessionAttribute("email");
            String ssn = (String) ctx.sessionAttribute("ssn");

            if (username == null || email == null || ssn == null) {
                ctx.result("Session data not found.");
                return;
            }

            String last4SSN = ssn.replaceAll("\\d(?=\\d{4})", "x");
            
            String responseHtml = "<html><body>"
                    + "<h1>User Information</h1>"
                    + "<p>Username: " + username + "</p>"
                    + "<p>Email: " + email + "</p>"
                    + "<p>Last 4 digits of SSN: " + last4SSN.substring(last4SSN.length() - 4) + "</p>"
                    + "</body></html>";

            ctx.result(responseHtml);
        });
    }
}


To run this application, you will need to include the Javalin dependency in your project's build file. For example, if you're using Maven, add the following to your `pom.xml`:


<dependency>
    <groupId>io.javalin</groupId>
    <artifactId>javalin</artifactId>
    <version>5.0.0</version>
</dependency>


For Gradle, add this to your `build.gradle` file:


implementation 'io.javalin:javalin:5.0.0'


Ensure you have the necessary session management in place when using Javalin.