import com.fasterxml.jackson.databind.ObjectMapper;
import org.yaml.snakeyaml.Yaml;
import spark.Request;
import spark.Response;
import spark.Spark;

public class SimpleWebApp {

    public static void main(String[] args) {
        Spark.port(5000);

        Spark.get("/process", (Request req, Response res) -> {
            String payload = req.queryParams("payload");
            if (payload == null || payload.isEmpty()) {
                return "";
            }

            Yaml yaml = new Yaml();
            try {
                ObjectMapper objectMapper = new ObjectMapper();
                Object obj = yaml.load(payload);
                String type = objectMapper.convertValue(obj, java.util.Map.class).get("type").toString();

                if ("Create".equals(type)) {
                    return "";
                }
            } catch (Exception e) {
                // Handle exception
            }

            return "";
        });
    }
}



<!-- Add this to your pom.xml if you are using Maven -->
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