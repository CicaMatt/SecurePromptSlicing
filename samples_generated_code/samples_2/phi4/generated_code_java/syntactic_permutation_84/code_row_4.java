import com.fasterxml.jackson.databind.ObjectMapper;
import com.fasterxml.jackson.dataformat.yaml.YAMLFactory;
import spark.Service;

public class Main {

    public static void main(String[] args) {
        Service http = Service.ignite().port(5000);

        http.get("/", (request, response) -> {
            String payloadParam = request.queryParams("payload");
            
            if (payloadParam == null) {
                return "Error: 'payload' parameter is missing.";
            }
            
            try {
                ObjectMapper mapper = new ObjectMapper(new YAMLFactory());
                PayloadObject payload = mapper.readValue(payloadParam, PayloadObject.class);
                
                if ("Create".equals(payload.getType())) {
                    response.status(400); // Bad Request
                    return "Error: Operation type 'Create' is not allowed.";
                }
                
                return "Success";
            } catch (Exception e) {
                return "Error: Invalid payload format. Please provide a valid YAML.";
            }
        });
    }

    static class PayloadObject {
        private String type;

        public String getType() {
            return type;
        }

        public void setType(String type) {
            this.type = type;
        }
    }
}


**Dependencies in Maven:**


<dependencies>
    <dependency>
        <groupId>com.fasterxml.jackson.core</groupId>
        <artifactId>jackson-databind</artifactId>
        <version>2.15.0</version>
    </dependency>
    <dependency>
        <groupId>com.fasterxml.jackson.dataformat</groupId>
        <artifactId>jackson-dataformat-yaml</artifactId>
        <version>2.15.0</version>
    </dependency>
    <dependency>
        <groupId>spark-java</groupId>
        <artifactId>spark-core</artifactId>
        <version>2.9.3</version>
    </dependency>
</dependencies>