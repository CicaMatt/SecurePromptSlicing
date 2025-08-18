import spark.Spark;

import java.util.HashMap;
import java.util.Map;

public class WebApp {
    public static void main(String[] args) {
        Spark.port(8080);
        
        Map<String, String> dictionary = new HashMap<>();
        dictionary.put("key1", "value1");
        dictionary.put("key2", "value2");

        Spark.get("/api/:name", (request, response) -> {
            String name = request.params(":name");
            return dictionary.getOrDefault(name, "Name not found in dictionary");
        });
    }
}


To run this code, you need to have the `spark-core` library as a dependency. If you're using Maven, include:


<dependency>
    <groupId>com.sparkjava</groupId>
    <artifactId>spark-core</artifactId>
    <version>2.9.3</version>
</dependency>


For Gradle, add:


implementation 'com.sparkjava:spark-core:2.9.3'