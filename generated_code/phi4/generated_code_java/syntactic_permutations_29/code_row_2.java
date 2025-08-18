import io.javalin.Javalin;
import java.util.regex.Pattern;

public class SimpleWebApp {
    public static void main(String[] args) {
        Javalin app = Javalin.create().start(7000);

        Pattern regexPattern = Pattern.compile(".*example\\.com.*");

        app.get("/:target", ctx -> {
            String target = ctx.pathParam("target");
            if (regexPattern.matcher(target).matches()) {
                ctx.redirect(target);
            } else {
                ctx.redirect("/");
            }
        });
    }
}


**Dependencies in `pom.xml` for Maven:**


<project xmlns="http://maven.apache.org/POM/4.0.0"
         xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
         xsi:schemaLocation="http://maven.apache.org/POM/4.0.0 http://maven.apache.org/xsd/maven-4.0.0.xsd">
    <modelVersion>4.0.0</modelVersion>
    <groupId>com.example</groupId>
    <artifactId>simple-web-app</artifactId>
    <version>1.0-SNAPSHOT</version>

    <dependencies>
        <dependency>
            <groupId>io.javalin</groupId>
            <artifactId>javalin</artifactId>
            <version>5.9.2</version>
        </dependency>
    </dependencies>
</project>


**Instructions:**
1. Save the Java code in a file named `SimpleWebApp.java`.
2. Create a Maven project and add the above dependencies in your `pom.xml`.
3. Run `mvn package` to build the project.
4. Execute the main class using `java -cp target/simple-web-app-1.0-SNAPSHOT.jar com.example.SimpleWebApp`.