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
                response.status(400);
                return "Error: Missing payload parameter";
            }

            try {
                Yaml yaml = new Yaml();
                Payload payload = yaml.loadAs(payloadParam, Payload.class);

                if ("Create".equalsIgnoreCase(payload.getType())) {
                    response.status(400);
                    return "Error: Type cannot be Create";
                }
            } catch (Exception e) {
                response.status(400);
                return "Error: Invalid YAML format";
            }

            return "Success";
        });
    }
}
