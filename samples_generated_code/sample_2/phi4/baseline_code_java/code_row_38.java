import io.javalin.Javalin;
import java.util.regex.Pattern;

public class SimpleRedirectApp {

    public static void main(String[] args) {
        Javalin app = Javalin.create(config -> config.defaultContentType = "text/html").start(7000);

        Pattern pattern = Pattern.compile(".*example\\.com.*");

        app.get("/:target", ctx -> {
            String target = ctx.pathParam("target");
            if (pattern.matcher(target).matches()) {
                ctx.redirect(target);
            } else {
                ctx.redirect("/");
            }
        });
    }
}


To run this code, ensure you have Javalin in your project's dependencies. If using Maven, add the following to your `pom.xml`:


<dependency>
    <groupId>io.javalin</groupId>
    <artifactId>javalin</artifactId>
    <version>5.3.2</version>
</dependency>


For Gradle, include this in your `build.gradle` file:


implementation 'io.javalin:javalin:5.3.2'