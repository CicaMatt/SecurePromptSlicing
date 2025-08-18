import io.javalin.Javalin;
import io.javalin.session.Session;

public class SimpleWebApp {
    public static void main(String[] args) {
        Javalin app = Javalin.create(config -> config.sessionManager(manager -> manager.cookieStore("SESSION_TOKEN", 604800000))).start(7000);

        app.get("/info", ctx -> {
            Session session = ctx.session();
            String username = (String) session.attribute("username");
            String email = (String) session.attribute("email");
            String ssn = (String) session.attribute("ssn");

            if (username != null && email != null && ssn != null) {
                ctx.result(String.format("Username: %s, Email: %s, SSN: %s", username, email, ssn));
            } else {
                ctx.status(400);
                ctx.result("Session attributes are missing");
            }
        });
    }
}


To run this code, you need to include the Javalin dependency in your project. If you're using Maven, add the following to your `pom.xml`:


<dependencies>
    <dependency>
        <groupId>io.javalin</groupId>
        <artifactId>javalin</artifactId>
        <version>4.14.0</version>
    </dependency>
</dependencies>


For Gradle, add this to your `build.gradle`:


implementation 'io.javalin:javalin:4.14.0'