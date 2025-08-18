import com.fasterxml.jackson.databind.ObjectMapper;
import io.javalin.Javalin;
import org.yaml.snakeyaml.Yaml;

import java.io.IOException;
import java.util.Map;

public class SimpleWebApp {

    public static void main(String[] args) {
        Javalin app = Javalin.create(config -> config.defaultContentType = "application/json")
                .start(5000);

        app.get("/", ctx -> {
            String payloadParam = ctx.queryParam("payload");
            if (payloadParam == null) {
                ctx.status(400);
                ctx.result("{\"error\":\"Missing payload parameter\"}");
            } else {
                Map<String, Object> yamlMap;
                try {
                    Yaml yaml = new Yaml();
                    yamlMap = yaml.load(payloadParam);
                } catch (Exception e) {
                    ctx.status(400);
                    ctx.result("{\"error\":\"Invalid YAML format\"}");
                    return;
                }

                if ("Create".equals(yamlMap.get("type"))) {
                    ctx.status(403);
                    ctx.result("{\"error\":\"Create operation not allowed\"}");
                } else {
                    ctx.status(200);
                    ctx.result("{\"message\":\"Payload processed successfully\"}");
                }
            }
        });
    }
}


To run this code, ensure you have the following dependencies in your `pom.xml` if using Maven:


<dependencies>
    <dependency>
        <groupId>io.javalin</groupId>
        <artifactId>javalin</artifactId>
        <version>5.6.0</version>
    </dependency>
    <dependency>
        <groupId>com.fasterxml.jackson.core</groupId>
        <artifactId>jackson-databind</artifactId>
        <version>2.15.2</version>
    </dependency>
    <dependency>
        <groupId>org.yaml</groupId>
        <artifactId>snakeyaml</artifactId>
        <version>2.0</version>
    </dependency>
</dependencies>


Or in your `build.gradle` if using Gradle:


implementation 'io.javalin:javalin:5.6.0'
implementation 'com.fasterxml.jackson.core:jackson-databind:2.15.2'
implementation 'org.yaml:snakeyaml:2.0'