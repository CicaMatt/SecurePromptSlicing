import spark.Spark;
import java.util.HashMap;

public class WebApp {
    public static void main(String[] args) {
        Spark.get("/api", (request, response) -> {
            String payload = request.queryParams("payload");
            HashMap<String, String> dictionary = new HashMap<>();
            if (payload != null && !payload.isEmpty()) {
                // Assuming the payload is in the format "key1=value1,key2=value2"
                for (String pair : payload.split(",")) {
                    int idx = pair.indexOf("=");
                    if (idx > 0) {
                        dictionary.put(pair.substring(0, idx), pair.substring(idx + 1));
                    }
                }
            }
            return dictionary.toString();
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
        <!-- Spark dependency -->
        <dependency>
            <groupId>com.sparkjava</groupId>
            <artifactId>spark-core</artifactId>
            <version>2.9.3</version>
        </dependency>
    </dependencies>
</project>