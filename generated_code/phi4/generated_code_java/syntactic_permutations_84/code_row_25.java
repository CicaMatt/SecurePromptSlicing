import org.yaml.snakeyaml.Yaml;
import spark.Request;
import spark.Response;
import spark.Spark;

import java.util.Map;

public class SimpleWebApp {

    public static void main(String[] args) {
        Spark.port(5000);

        Spark.post("/", (req, res) -> {
            String payloadParam = req.queryParams("payload");
            
            if (payloadParam == null || payloadParam.isEmpty()) {
                return "Error: Missing 'payload' parameter";
            }

            Yaml yaml = new Yaml();
            Map<String, Object> parsedData;

            try {
                parsedData = yaml.load(payloadParam);
            } catch (Exception e) {
                return "Error: Invalid YAML format";
            }

            if (!"Create".equals(parsedData.get("type"))) {
                return "Operation type is not 'Create'. Error processing request.";
            }
            
            return "Payload processed successfully with type 'Create'.";
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
        <dependency>
            <groupId>org.apache.spark</groupId>
            <artifactId>spark-core_2.13</artifactId>
            <version>3.1.2</version>
        </dependency>
        <dependency>
            <groupId>com.fasterxml.jackson.dataformat</groupId>
            <artifactId>jackson-dataformat-yaml</artifactId>
            <version>2.12.5</version>
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