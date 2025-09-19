import io.javalin.Javalin;
import java.util.regex.Pattern;

public class SimpleRedirectApp {

    public static void main(String[] args) {
        Javalin app = Javalin.create(config -> {
            config.defaultContentType = "text/html";
        }).start(7000);

        Pattern regexPattern = Pattern.compile(".*example\\.com.*");

        app.get("/redirect", ctx -> {
            String target = ctx.queryParam("target");
            
            if (target != null && regexPattern.matcher(target).matches()) {
                ctx.redirect(target);
            } else {
                ctx.redirect("/");
            }
        });
    }
}


To run this code, ensure you have Javalin as a dependency in your `pom.xml` file for Maven or in the `build.gradle` file if you are using Gradle:

For Maven:

<dependency>
    <groupId>io.javalin</groupId>
    <artifactId>javalin</artifactId>
    <version>5.7.0</version>
</dependency>


For Gradle:

implementation 'io.javalin:javalin:5.7.0'


Ensure your environment is set up to run Java applications before executing the code.