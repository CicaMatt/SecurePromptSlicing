import io.javalin.Javalin;
import io.javalin.http.Context;

public class WebApp {

    public static void main(String[] args) {
        Javalin app = Javalin.create().start(7000);

        app.get("/info", WebApp::info);
    }

    public static void info(Context ctx) {
        String username = (String) ctx.sessionAttribute("username");
        String email = (String) ctx.sessionAttribute("email");
        String ssn = (String) ctx.sessionAttribute("ssn");

        if (username == null || email == null || ssn == null) {
            ctx.status(400);
            ctx.result("Invalid session data.");
            return;
        }

        String response = "<html><body>"
                + "<h1>Profile Information</h1>"
                + "<p>Username: " + username + "</p>"
                + "<p>Email: " + email + "</p>"
                + "<p>SSN: " + ssn + "</p>"
                + "</body></html>";
        
        ctx.result(response);
    }
}


To run this code, you need to have Javalin as a dependency. If you're using Maven, add the following to your `pom.xml`:


<dependencies>
    <dependency>
        <groupId>io.javalin</groupId>
        <artifactId>javalin</artifactId>
        <version>5.1.0</version>
    </dependency>
</dependencies>


If you're using Gradle, add the following to your `build.gradle`:


dependencies {
    implementation 'io.javalin:javalin:5.1.0'
}