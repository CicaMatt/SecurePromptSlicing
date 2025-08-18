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
        String username = (String) ctx.sessionAttribute("username");
        String email = (String) ctx.sessionAttribute("email");
        String ssn = (String) ctx.sessionAttribute("ssn");

        if (username == null || email == null || ssn == null) {
            ctx.result("Missing session attributes.");
            return;
        }

        String last4SSN = ssn.substring(ssn.length() - 4);
        
        ctx.result("<html><body>"
                    + "<h1>Info</h1>"
                    + "<p>Username: " + username + "</p>"
                    + "<p>Email: " + email + "</p>"
                    + "<p>Last 4 digits of SSN: " + last4SSN + "</p>"
                + "</body></html>");
    }
}


Make sure you have the following dependencies in your `build.gradle` or equivalent:


dependencies {
    implementation 'io.javalin:javalin:5.6.0'
}