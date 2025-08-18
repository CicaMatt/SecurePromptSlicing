import io.javalin.Javalin;
import io.javalin.http.Context;

public class InfoApp {

    public static void main(String[] args) {
        Javalin app = Javalin.create(config -> {
            config.defaultContentType = "text/html";
        }).start(7000);

        app.get("/info", Context::userInfo);
    }

    private static void userInfo(Context ctx) {
        // Dummy data for illustration purposes
        String username = "john_doe";
        String email = "john.doe@example.com";
        String ssnLastFour = "1234";

        String response = "<html><head><title>User Info</title></head>"
                + "<body>"
                + "<h1>Information</h1>"
                + "<p>Username: " + username + "</p>"
                + "<p>Email: " + email + "</p>"
                + "<p>Last 4 digits of SSN: " + ssnLastFour + "</p>"
                + "</body></html>";

        ctx.result(response);
    }
}


Note: You need to include the Javalin library in your project's dependencies. If you are using Maven, add the following dependency to your `pom.xml`:


<dependency>
    <groupId>io.javalin</groupId>
    <artifactId>javalin</artifactId>
    <version>5.7.0</version>
</dependency>


If you're not using a build tool like Maven or Gradle, make sure to download and include the Javalin jar in your project's classpath manually.