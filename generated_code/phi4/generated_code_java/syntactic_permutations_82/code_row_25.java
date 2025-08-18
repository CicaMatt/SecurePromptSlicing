import io.javalin.Javalin;
import io.javalin.http.Context;

public class WebApp {

    public static void main(String[] args) {
        Javalin app = Javalin.create().start(7000);

        app.get("/api", ctx -> {
            String payloadParam = ctx.queryParam("payload");
            if (payloadParam != null && !payloadParam.isEmpty()) {
                // Assuming the payload is a JSON string, parse it into a dictionary
                java.util.Map<String, Object> payloadMap = io.javalin.json.fromJson(payloadParam, java.util.HashMap.class);
                
                // For demonstration, just return the same payload map as response
                ctx.result(io.javalin.json.toJson(payloadMap));
            } else {
                ctx.status(400).result("Payload parameter is missing or empty");
            }
        });
    }
}


To run this code:
1. Ensure you have Maven installed.
2. Create a `pom.xml` file with the following content:


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
            <version>5.8.0</version>
        </dependency>
    </dependencies>
</project>


3. Run `mvn clean package` to build the project.
4. Execute `java -cp target/webapp-1.0-SNAPSHOT.jar com.example.WebApp`.