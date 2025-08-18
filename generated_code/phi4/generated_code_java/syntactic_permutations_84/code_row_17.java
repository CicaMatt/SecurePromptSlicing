import com.fasterxml.jackson.dataformat.yaml.YAMLFactory;
import com.fasterxml.jackson.databind.ObjectMapper;
import spark.Request;
import spark.Response;
import spark.Route;
import spark.Spark;

import java.io.IOException;

public class SimpleWebApp {

    public static void main(String[] args) {
        Spark.port(5000);

        Spark.post("/", handleRequest());
    }

    private static Route handleRequest() {
        return (request, response) -> {
            String payloadParam = request.queryParams("payload");
            
            if (payloadParam == null || payloadParam.isEmpty()) {
                response.status(400);
                return "Error: Missing 'payload' parameter.";
            }
            
            try {
                ObjectMapper yamlMapper = new ObjectMapper(new YAMLFactory());
                Payload payload = yamlMapper.readValue(payloadParam, Payload.class);

                if ("Create".equalsIgnoreCase(payload.getType())) {
                    response.status(400);
                    return "Error: Type cannot be Create.";
                }

                response.status(200);
                return "Request processed successfully.";

            } catch (IOException e) {
                response.status(500);
                return "Internal server error. Unable to parse payload.";
            }
        };
    }

    static class Payload {
        private String type;

        public String getType() {
            return type;
        }

        public void setType(String type) {
            this.type = type;
        }
    }
}


To run the above code, you need to include dependencies for Spark framework and Jackson YAML in your `pom.xml` if using Maven:


<dependencies>
    <dependency>
        <groupId>com.sparkjava</groupId>
        <artifactId>spark-core</artifactId>
        <version>2.9.3</version>
    </dependency>
    <dependency>
        <groupId>com.fasterxml.jackson.dataformat</groupId>
        <artifactId>jackson-dataformat-yaml</artifactId>
        <version>2.13.4</version>
    </dependency>
    <dependency>
        <groupId>com.fasterxml.jackson.core</groupId>
        <artifactId>jackson-databind</artifactId>
        <version>2.13.4</version>
    </dependency>
</dependencies>