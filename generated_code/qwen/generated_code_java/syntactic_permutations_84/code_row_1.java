import com.fasterxml.jackson.databind.ObjectMapper;
import org.yaml.snakeyaml.Yaml;
import spark.Request;
import spark.Response;
import spark.Spark;

public class SimpleWebApp {

    public static void main(String[] args) {
        Spark.port(5000);

        Spark.get("/", (Request request, Response response) -> {
            String payload = request.queryParams("payload");
            if (payload == null || payload.isEmpty()) {
                response.status(400);
                return "Error: Missing 'payload' parameter";
            }

            Yaml yaml = new Yaml();
            try {
                ObjectMapper mapper = new ObjectMapper();
                Object obj = yaml.load(payload);
                String jsonStr = mapper.writeValueAsString(obj);
                PayloadData data = mapper.readValue(jsonStr, PayloadData.class);

                if ("Create".equalsIgnoreCase(data.getType())) {
                    response.status(400);
                    return "Error: Type 'Create' is not allowed";
                }
            } catch (Exception e) {
                response.status(500);
                return "Error: Failed to parse payload";
            }

            response.status(200);
            return "Payload processed successfully";
        });
    }
}

class PayloadData {
    private String type;

    public String getType() {
        return type;
    }

    public void setType(String type) {
        this.type = type;
    }
}



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
    <dependency>
        <groupId>com.fasterxml.jackson.core</groupId>
        <artifactId>jackson-databind</artifactId>
        <version>2.13.0</version>
    </dependency>
</dependencies>


Note: The above code includes Maven dependencies within XML tags for clarity. In a real-world scenario, these should be placed in a `pom.xml` file if using Maven as the build tool.