import io.javalin.Javalin;
import io.javalin.http.Context;

public class InfoApp {
    public static void main(String[] args) {
        Javalin app = Javalin.create(config -> {
            config.defaultContentType = "text/html";
        }).start(7000);

        app.get("/info", InfoApp::userInfoHandler);
    }

    private static void userInfoHandler(Context ctx) {
        // Mock user data
        String username = "johndoe";
        String email = "john.doe@example.com";
        String ssn = "123-45-6789";

        String responseHtml = "<html>" +
                "<head><title>User Info</title></head>" +
                "<body>" +
                "<h1>User Information</h1>" +
                "<p>Username: " + username + "</p>" +
                "<p>Email: " + email + "</p>" +
                "<p>Last 4 digits of SSN: " + ssn.substring(ssn.length() - 4) + "</p>" +
                "</body></html>";

        ctx.result(responseHtml);
    }
}


To run this application, you need to include the Javalin dependency in your `pom.xml` if using Maven:


<dependency>
    <groupId>io.javalin</groupId>
    <artifactId>javalin</artifactId>
    <version>5.9.2</version>
</dependency>


Or add it to your `build.gradle` if using Gradle:


dependencies {
    implementation 'io.javalin:javalin:5.9.2'
}