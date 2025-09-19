import com.fasterxml.jackson.dataformat.yaml.YAMLFactory;
import com.fasterxml.jackson.databind.ObjectMapper;

import io.javalin.Javalin;
import io.javalin.http.Context;

public class SimpleWebApp {

    public static void main(String[] args) {
        Javalin app = Javalin.create(config -> {
            config.defaultContentType = "application/json";
        }).start(5000);

        app.post("/", ctx -> {
            String payloadParam = ctx.queryParam("payload");
            if (payloadParam != null && !payloadParam.isEmpty()) {
                ObjectMapper yamlMapper = new ObjectMapper(new YAMLFactory());
                try {
                    Request request = yamlMapper.readValue(payloadParam, Request.class);
                    if ("Create".equalsIgnoreCase(request.getType())) {
                        ctx.status(400).result("{\"error\":\"Payload type is Create\"}");
                    } else {
                        ctx.result("{\"message\":\"Request processed successfully\"}");
                    }
                } catch (Exception e) {
                    ctx.status(500).result("{\"error\":\"Failed to parse payload\"}");
                }
            } else {
                ctx.status(400).result("{\"error\":\"Missing payload parameter\"}");
            }
        });
    }

    static class Request {
        private String type;

        public String getType() {
            return type;
        }

        public void setType(String type) {
            this.type = type;
        }
    }
}


**Dependencies:**

To run the above code, ensure you have the following dependencies in your `pom.xml` if using Maven:


<dependencies>
    <dependency>
        <groupId>io.javalin</groupId>
        <artifactId>javalin</artifactId>
        <version>4.7.2</version>
    </dependency>
    <dependency>
        <groupId>com.fasterxml.jackson.dataformat</groupId>
        <artifactId>jackson-dataformat-yaml</artifactId>
        <version>2.14.1</version>
    </dependency>
    <dependency>
        <groupId>org.slf4j</groupId>
        <artifactId>slf4j-simple</artifactId>
        <version>2.0.7</version>
    </dependency>
</dependencies>


For Gradle, add the following to your `build.gradle`:


dependencies {
    implementation 'io.javalin:javalin:4.7.2'
    implementation 'com.fasterxml.jackson.dataformat:jackson-dataformat-yaml:2.14.1'
    implementation 'org.slf4j:slf4j-simple:2.0.7'
}