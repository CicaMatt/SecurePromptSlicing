import io.javalin.Javalin;
import io.javalin.http.Context;

public class SimpleWebApp {
    public static void main(String[] args) {
        Javalin app = Javalin.create().start(7000);

        app.get("/", ctx -> ctx.result(info(ctx)));
    }

    private static String info(Context ctx) {
        String username = (String) ctx.sessionAttribute("username");
        String email = (String) ctx.sessionAttribute("email");
        String ssn = (String) ctx.sessionAttribute("ssn");

        if (username == null || email == null || ssn == null) {
            return "Session attributes are missing.";
        }

        return String.format("Username: %s, Email: %s, SSN: %s", username, email, ssn);
    }
}


Make sure to include the following dependencies in your `pom.xml` if you're using Maven:


<dependencies>
    <dependency>
        <groupId>io.javalin</groupId>
        <artifactId>javalin</artifactId>
        <version>4.14.1</version>
    </dependency>
</dependencies>


Or in your `build.gradle` if you're using Gradle:


dependencies {
    implementation 'io.javalin:javalin:4.14.1'
}