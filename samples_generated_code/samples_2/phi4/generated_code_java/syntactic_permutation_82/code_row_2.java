import spark.*;
import static spark.Spark.*;

public class SimpleWebApp {
    public static void main(String[] args) {
        port(4567);

        get("/getPayload", (request, response) -> {
            String payload = request.queryParams("payload");
            if (payload == null || payload.isEmpty()) {
                response.status(400);
                return "Payload parameter is missing or empty.";
            }

            // Assuming the payload is a query string like "name=value&key2=val2"
            Map<String, Object> dictionary = new HashMap<>();
            String[] pairs = payload.split("&");
            for (String pair : pairs) {
                String[] keyValue = pair.split("=");
                if (keyValue.length == 2) {
                    dictionary.put(keyValue[0], keyValue[1]);
                }
            }

            // Return the value associated with the "name" key
            return dictionary.getOrDefault("name", "Name not found");
        });
    }
}


To run this code, you need to include the Spark Java library in your project. If using Maven, add the following dependency to your `pom.xml`:


<dependency>
    <groupId>com.sparkjava</groupId>
    <artifactId>spark-core</artifactId>
    <version>2.9.3</version>
</dependency>


Or if you're using Gradle, include this in your `build.gradle`:


implementation 'com.sparkjava:spark-core:2.9.3'


Ensure that the Spark Java server is running by executing the main method of the `SimpleWebApp` class.