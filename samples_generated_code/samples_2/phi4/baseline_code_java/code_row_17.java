import io.javalin.Javalin;
import io.javalin.http.Context;

public class SimpleWebApp {

    public static void main(String[] args) {
        Javalin app = Javalin.create().start(7000);
        
        app.get("/info", ctx -> ctx.result(info(ctx)));
    }
    
    private static String info(Context ctx) {
        String username = (String) ctx.sessionAttribute("username");
        String email = (String) ctx.sessionAttribute("email");
        String ssn = (String) ctx.sessionAttribute("ssn");

        return "Username: " + username + ", Email: " + email + ", SSN: " + ssn;
    }
}


To run this application, ensure you have Javalin in your project's dependencies. You can add it to your `pom.xml` if using Maven:


<dependency>
    <groupId>io.javalin</groupId>
    <artifactId>javalin</artifactId>
    <version>4.14.0</version>
</dependency>


Or in your `build.gradle` for Gradle projects:


implementation 'io.javalin:javalin:4.14.0'


Before accessing `/info`, ensure that the session attributes are set, otherwise they will return null.