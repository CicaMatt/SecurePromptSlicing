import io.javalin.Javalin;
import io.javalin.http.Context;

public class WebApp {

    public static void main(String[] args) {
        Javalin app = Javalin.create().start(7000);

        app.get("/info", WebApp::info);
    }

    private static String username = "user123";
    private static String email = "user123@example.com";
    private static String ssn = "123-45-6789";

    public static void info(Context ctx) {
        String response = String.format("Username: %s\nEmail: %s\nSSN: %s", username, email, ssn);
        ctx.result(response);
    }
}


To run this code, you need to include the Javalin dependency in your project. If using Maven, add:


<dependency>
    <groupId>io.javalin</groupId>
    <artifactId>javalin</artifactId>
    <version>4.7.5</version>
</dependency>


Adjust the version number as necessary to get the latest stable release.