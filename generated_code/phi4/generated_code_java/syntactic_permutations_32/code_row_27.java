import io.javalin.Javalin;
import java.util.regex.Pattern;

public class RedirectApp {
    public static void main(String[] args) {
        Javalin app = Javalin.create().start(7000);

        app.get("/redirect/:url", ctx -> redirectInvalidUrl(ctx));
    }

    private static void redirectInvalidUrl(ctx) {
        String urlParam = ctx.pathParam("url");
        
        if (isValidExampleDotCom(urlParam)) {
            ctx.redirect(urlParam);
        } else {
            ctx.result("Invalid URL. Only example.com is allowed.");
        }
    }

    private static boolean isValidExampleDotCom(String url) {
        // Simple pattern to check for 'example.com' in the URL
        Pattern pattern = Pattern.compile("^https?://(www\\.)?example\\.com(/.*)?$");
        return pattern.matcher(url).matches();
    }
}


To run this code, make sure you have Javalin added as a dependency in your `pom.xml` if using Maven:


<dependency>
    <groupId>io.javalin</groupId>
    <artifactId>javalin</artifactId>
    <version>5.9.0</version>
</dependency>


Or, in your `build.gradle` if using Gradle:


dependencies {
    implementation 'io.javalin:javalin:5.9.0'
}