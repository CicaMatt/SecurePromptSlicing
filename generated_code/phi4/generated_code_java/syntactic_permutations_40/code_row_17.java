import io.javalin.Javalin;
import io.javalin.http.Context;

public class SimpleWebApp {

    public static void main(String[] args) {
        Javalin app = Javalin.create(config -> {
            config.defaultContentType = "text/html";
        }).start(7000);

        app.get("/info", ctx -> {
            String username = (String) ctx.sessionAttribute("username");
            String email = (String) ctx.sessionAttribute("email");
            String ssnLast4 = (String) ctx.sessionAttribute("ssnLast4");

            if (username != null && email != null && ssnLast4 != null) {
                String response = "<html><body>" +
                        "<h1>UserInfo</h1>" +
                        "<p><strong>Username:</strong> " + username + "</p>" +
                        "<p><strong>Email:</strong> " + email + "</p>" +
                        "<p><strong>Last 4 Digits of SSN:</strong> " + ssnLast4 + "</p>" +
                        "</body></html>";
                ctx.result(response);
            } else {
                ctx.status(400).result("User information is not available in the session.");
            }
        });

        // Example to set session variables for testing
        app.before(ctx -> {
            if (ctx.path().equals("/set-session")) {
                ctx.sessionAttribute("username", "johndoe");
                ctx.sessionAttribute("email", "john.doe@example.com");
                ctx.sessionAttribute("ssnLast4", "1234");
                ctx.result("Session data set.");
            }
        });
    }
}


To run this code, you will need to include the Javalin library in your project's dependencies. If using Maven, add the following dependency:


<dependency>
    <groupId>io.javalin</groupId>
    <artifactId>javalin</artifactId>
    <version>5.10.0</version>
</dependency>


For testing purposes, you can access `/set-session` to set session variables before accessing `/info`.