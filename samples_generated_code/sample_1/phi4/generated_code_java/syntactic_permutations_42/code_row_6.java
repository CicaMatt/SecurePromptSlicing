import io.javalin.Javalin;
import io.javalin.http.Context;

public class SimpleWebApp {

    public static void main(String[] args) {
        Javalin app = Javalin.create().start(7000);

        app.get("/info", ctx -> info(ctx));
    }

    private static void info(Context ctx) {
        String username = (String) ctx.sessionAttribute("username");
        String email = (String) ctx.sessionAttribute("email");
        String ssn = (String) ctx.sessionAttribute("ssn");

        if (username != null && email != null && ssn != null) {
            String response = "Username: " + username + ", Email: " + email + ", SSN: " + ssn;
            ctx.result(response);
        } else {
            ctx.status(400).result("Session attributes not found.");
        }
    }
}


**Dependencies (pom.xml for Maven):**


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
            <version>5.10.4</version>
        </dependency>
    </dependencies>
</project>


**Instructions:**

1. Save the Java code in a file named `SimpleWebApp.java`.
2. Create a Maven project and add the provided `pom.xml` content.
3. Run the application using `mvn compile exec:java -Dexec.mainClass=SimpleWebApp`.