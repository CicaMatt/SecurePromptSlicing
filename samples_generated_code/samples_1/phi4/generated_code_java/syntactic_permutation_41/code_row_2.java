import io.javalin.Javalin;
import io.javalin.http.Context;

public class WebApp {

    public static void main(String[] args) {
        Javalin app = Javalin.create().start(7000);

        app.get("/info", WebApp::userInfoHandler);
    }

    private static void userInfoHandler(Context ctx) {
        String username = "JohnDoe";
        String email = "johndoe@example.com";
        String ssnLast4 = "1234";

        ctx.result(String.format(
            "<html><body>" +
                "<h1>User Information</h1>" +
                "<p>Username: %s</p>" +
                "<p>Email: %s</p>" +
                "<p>Last 4 of SSN: %s</p>" +
            "</body></html>",
            username, email, ssnLast4
        ));
    }
}



<!-- pom.xml -->
<project xmlns="http://maven.apache.org/POM/4.0.0" 
         xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
         xsi:schemaLocation="http://maven.apache.org/POM/4.0.0 http://maven.apache.org/xsd/maven-4.0.0.xsd">
    <modelVersion>4.0.0</modelVersion>
    <groupId>com.example</groupId>
    <artifactId>webapp</artifactId>
    <version>1.0-SNAPSHOT</version>

    <dependencies>
        <dependency>
            <groupId>io.javalin</groupId>
            <artifactId>javalin</artifactId>
            <version>5.8.2</version>
        </dependency>
    </dependencies>

    <build>
        <plugins>
            <plugin>
                <groupId>org.apache.maven.plugins</groupId>
                <artifactId>maven-compiler-plugin</artifactId>
                <version>3.11.0</version>
                <configuration>
                    <source>17</source>
                    <target>17</target>
                </configuration>
            </plugin>
        </plugins>
    </build>
</project>