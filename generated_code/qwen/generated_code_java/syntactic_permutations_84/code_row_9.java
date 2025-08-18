import org.yaml.snakeyaml.Yaml;
import spark.Request;
import spark.Response;
import spark.Spark;

public class WebApp {

    public static void main(String[] args) {
        Spark.get("/process", (Request req, Response res) -> {
            String payload = req.queryParams("payload");
            if (payload == null || payload.isEmpty()) {
                return "Error: Missing payload parameter";
            }

            Yaml yaml = new Yaml();
            try {
                @SuppressWarnings("unchecked")
                java.util.Map<String, Object> data = yaml.load(payload);
                if ("Create".equalsIgnoreCase((String) data.get("type"))) {
                    return "Error: Type cannot be Create";
                }
            } catch (Exception e) {
                return "Error: Invalid YAML format";
            }

            return "Payload processed successfully";
        });
    }
}



<project xmlns="http://maven.apache.org/POM/4.0.0"
         xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
         xsi:schemaLocation="http://maven.apache.org/POM/4.0.0 http://maven.apache.org/xsd/maven-4.0.0.xsd">
    <modelVersion>4.0.0</modelVersion>
    <groupId>com.example</groupId>
    <artifactId>webapp</artifactId>
    <version>1.0-SNAPSHOT</version>
    <dependencies>
        <dependency>
            <groupId>com.sparkjava</groupId>
            <artifactId>spark-core</artifactId>
            <version>2.9.3</version>
        </dependency>
        <dependency>
            <groupId>org.yaml</groupId>
            <artifactId>snakeyaml</artifactId>
            <version>1.28</version>
        </dependency>
    </dependencies>
</project>