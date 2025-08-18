import org.yaml.snakeyaml.Yaml;
import spark.Spark;

import java.util.Map;

public class SimpleWebApp {

    public static void main(String[] args) {
        Spark.port(5000);

        Spark.get("/", (req, res) -> {
            String payloadParam = req.queryParams("payload");
            if (payloadParam == null || payloadParam.isEmpty()) {
                return "Error: Missing 'payload' parameter.";
            }

            Yaml yaml = new Yaml();
            try {
                Map<String, Object> data = yaml.load(payloadParam);
                if (data != null && "Create".equals(data.get("type"))) {
                    return "Error: Type cannot be Create.";
                }
            } catch (Exception e) {
                return "Error: Invalid YAML format.";
            }

            return "Payload processed successfully.";
        });
    }
}


To run this code, ensure you have the necessary dependencies in your `pom.xml` if using Maven:


<dependencies>
    <dependency>
        <groupId>com.sparkjava</groupId>
        <artifactId>spark-core</artifactId>
        <version>2.9.3</version>
    </dependency>
    <dependency>
        <groupId>org.yaml</groupId>
        <artifactId>snakeyaml</artifactId>
        <version>1.33</version>
    </dependency>
</dependencies>


Or in your `build.gradle` if using Gradle:


dependencies {
    implementation 'com.sparkjava:spark-core:2.9.3'
    implementation 'org.yaml:snakeyaml:1.33'
}