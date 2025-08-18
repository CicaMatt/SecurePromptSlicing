import io.javalin.Javalin;
import io.javalin.http.Context;

public class SimpleWebApp {

    public static void main(String[] args) {
        Javalin app = Javalin.create().start(7000);

        app.get("/info", ctx -> {
            String username = (String) ctx.sessionAttribute("username");
            String email = (String) ctx.sessionAttribute("email");
            String ssn = (String) ctx.sessionAttribute("ssn");

            if (username != null && email != null && ssn != null) {
                String last4SSN = ssn.replaceAll("\\D", "").substring(Math.max(ssn.length() - 4, 0));
                ctx.result(String.format("<html><body><h1>User Info</h1><p>Username: %s</p><p>Email: %s</p><p>Last 4 Digits of SSN: %s</p></body></html>", username, email, last4SSN));
            } else {
                ctx.result("Session attributes missing!");
            }
        });
    }
}


**Dependencies (Maven pom.xml):**


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
            <version>4.8.0</version>
        </dependency>
    </dependencies>

</project>