import io.javalin.Javalin;
import org.yaml.snakeyaml.Yaml;

import java.util.Map;

public class SimpleWebApp {
    public static void main(String[] args) {
        Javalin app = Javalin.create().start(5000);

        app.post("/checkRequest", ctx -> {
            String payloadParam = ctx.queryParam("payload");
            if (payloadParam == null || payloadParam.isEmpty()) {
                ctx.status(400).result("{\"error\":\"Payload parameter is required.\"}");
                return;
            }

            Yaml yaml = new Yaml();
            Map<String, Object> map = yaml.load(payloadParam);

            if (!map.containsKey("type")) {
                ctx.status(400).result("{\"error\":\"The payload must contain a 'type' field.\"}");
                return;
            }

            String type = (String) map.get("type");
            if ("Create".equals(type)) {
                ctx.status(400).result("{\"error\":\"Operation of type 'Create' is not allowed.\"}");
            } else {
                ctx.result("{\"message\":\"Request processed successfully.\"}");
            }
        });
    }
}



<!-- pom.xml -->
<project xmlns="http://maven.apache.org/POM/4.0.0"
         xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
         xsi:schemaLocation="http://maven.apache.org/POM/4.0.0 http://maven.apache.org/xsd/maven-4.0.0.xsd">
    <modelVersion>4.0.0</modelVersion>

    <groupId>com.example</groupId>
    <artifactId>simple-web-app</artifactId>
    <version>1.0-SNAPSHOT</version>

    <dependencies>
        <!-- Javalin -->
        <dependency>
            <groupId>io.javalin</groupId>
            <artifactId>javalin</artifactId>
            <version>4.14.0</version>
        </dependency>
        
        <!-- SnakeYAML -->
        <dependency>
            <groupId>org.yaml</groupId>
            <artifactId>snakeyaml</artifactId>
            <version>1.33</version>
        </dependency>
    </dependencies>

    <build>
        <plugins>
            <plugin>
                <groupId>org.apache.maven.plugins</groupId>
                <artifactId>maven-compiler-plugin</artifactId>
                <version>3.8.1</version>
                <configuration>
                    <source>11</source>
                    <target>11</target>
                </configuration>
            </plugin>
        </plugins>
    </build>
</project>