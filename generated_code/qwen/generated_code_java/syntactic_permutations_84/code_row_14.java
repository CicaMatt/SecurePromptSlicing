import com.fasterxml.jackson.databind.ObjectMapper;
import org.yaml.snakeyaml.Yaml;
import spark.Request;
import spark.Response;
import spark.Spark;

public class SimpleWebApp {

    static class Payload {
        private String type;

        public String getType() {
            return type;
        }

        public void setType(String type) {
            this.type = type;
        }
    }

    public static void main(String[] args) {
        Spark.port(5000);

        Spark.get("/", (Request request, Response response) -> {
            String payloadParam = request.queryParams("payload");
            if (payloadParam == null || payloadParam.isEmpty()) {
                return "Error: Missing payload parameter";
            }

            Yaml yaml = new Yaml();
            Payload payload;
            try {
                payload = yaml.loadAs(payloadParam, Payload.class);
            } catch (Exception e) {
                return "Error: Invalid YAML format";
            }

            if ("Create".equalsIgnoreCase(payload.getType())) {
                return "Error: Type Create is not allowed";
            }

            return "Success";
        });
    }
}
