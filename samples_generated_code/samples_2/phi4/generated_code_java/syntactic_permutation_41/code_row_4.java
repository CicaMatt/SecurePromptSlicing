import io.javalin.Javalin;
import io.javalin.http.Context;

public class WebApp {

    public static void main(String[] args) {
        Javalin app = Javalin.create().start(7000);

        app.get("/info", ctx -> {
            String username = "JohnDoe"; // Replace with actual user data retrieval logic
            String email = "johndoe@example.com"; // Replace with actual user data retrieval logic
            String ssnLast4 = "1234"; // Replace with actual user data retrieval logic

            String userInfo = "<html>" +
                    "<head><title>User Information</title></head>" +
                    "<body>" +
                    "<h1>User Information</h1>" +
                    "<p>Username: " + username + "</p>" +
                    "<p>Email: " + email + "</p>" +
                    "<p>Last 4 digits of SSN: " + ssnLast4 + "</p>" +
                    "</body>" +
                    "</html>";

            ctx.result(userInfo);
        });
    }
}


To run this code, you need to add the Javalin dependency to your project. If using Maven, include the following in your `pom.xml`:


<dependency>
    <groupId>io.javalin</groupId>
    <artifactId>javalin</artifactId>
    <version>4.12.0</version>
</dependency>


For Gradle, add this to your `build.gradle`:


implementation 'io.javalin:javalin:4.12.0'