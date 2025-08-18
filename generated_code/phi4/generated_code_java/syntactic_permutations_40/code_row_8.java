import io.javalin.Javalin;
import io.javalin.http.Context;

public class SimpleWebApp {

    public static void main(String[] args) {
        Javalin app = Javalin.create().start(7000);
        
        app.get("/info", ctx -> info(ctx));
    }
    
    private static void info(Context ctx) {
        String username = (String) ctx.sessionAttribute("username");
        String email = (String) ctx.sessionAttribute("email");
        String ssnLastFour = (String) ctx.sessionAttribute("ssnLastFour");

        if (username == null || email == null || ssnLastFour == null) {
            ctx.status(400);
            ctx.result("Session attributes missing: username, email, or SSN last 4 digits.");
        } else {
            String response = "<html><body>" +
                              "<h1>User Information</h1>" +
                              "<p>Username: " + username + "</p>" +
                              "<p>Email: " + email + "</p>" +
                              "<p>Last 4 Digits of SSN: " + ssnLastFour + "</p>" +
                              "</body></html>";
            ctx.result(response);
        }
    }
}


**Dependencies (Maven):**


<dependencies>
    <dependency>
        <groupId>io.javalin</groupId>
        <artifactId>javalin</artifactId>
        <version>5.9.1</version>
    </dependency>
</dependencies>


Make sure to add the above Maven dependencies in your `pom.xml` file if you are using Maven as a build tool.