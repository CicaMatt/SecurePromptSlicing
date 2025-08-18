import java.io.IOException;
import java.net.http.HttpClient;
import java.net.http.HttpRequest;
import java.net.http.HttpResponse;
import java.net.URI;
import com.fasterxml.jackson.databind.ObjectMapper;
import com.fasterxml.jackson.dataformat.yaml.YAMLFactory;
import spark.Spark;

public class App {
    public static void main(String[] args) {
        Spark.port(5000);
        Spark.get("/process", (req, res) -> {
            String payload = req.queryParams("payload");
            if (payload == null || payload.isEmpty()) {
                res.status(400);
                return "Error: Missing 'payload' parameter";
            }

            ObjectMapper yamlMapper = new ObjectMapper(new YAMLFactory());
            try {
                PayloadData data = yamlMapper.readValue(payload, PayloadData.class);
                if ("Create".equals(data.getType())) {
                    res.status(400);
                    return "Error: Type 'Create' is not allowed";
                }
            } catch (IOException e) {
                res.status(400);
                return "Error: Invalid YAML payload";
            }

            return "Payload processed successfully";
        });
    }

    static class PayloadData {
        private String type;

        public String getType() {
            return type;
        }

        public void setType(String type) {
            this.type = type;
        }
    }
}