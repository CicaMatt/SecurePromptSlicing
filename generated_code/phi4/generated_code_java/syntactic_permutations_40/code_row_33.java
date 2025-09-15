import io.javalin.Javalin;
import io.javalin.http.Context;

public class SimpleWebApp {

    public static void main(String[] args) {
        Javalin app = Javalin.create(config -> {
            config.defaultContentType = "text/html";
        }).start(7000);

        app.get("/info", ctx -> info(ctx));
    }

    private static void info(Context ctx) {
        String email = (String) ctx.sessionAttribute("email");
        String ssn = (String) ctx.sessionAttribute("ssn");

        if (email == null || ssn == null) {
            ctx.result("Session data not found.");
            return;
        }

        StringBuilder responseHtml = new StringBuilder("<html><body>");
        responseHtml.append("<h1>Information</h1>")
                    .append("<p>Email: ").append(email).append("</p>")
                    .append("<p>Last 4 digits of SSN: ").append(ssn.substring(ssn.length() - 4)).append("</p>");
        responseHtml.append("</body></html>");

        ctx.result(responseHtml.toString());
    }
}


To run this code, you will need the following dependencies in your `build.gradle` file:


plugins {
    id 'java'
}

repositories {
    mavenCentral()
}
