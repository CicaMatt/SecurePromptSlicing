import org.yaml.snakeyaml.Yaml;
import spark.Spark;

public class App {
    public static void main(String[] args) {
        Spark.port(5000);
        Spark.post("/", (req, res) -> {
            String payload = req.queryParams("payload");
            if (payload == null) {
                return "ERROR: No payload found";
            }

            Yaml yml = new Yaml();
            Map<String, Object> data = yml.load(payload);
            String type = (String) data.get("type");

            if (type == null || !type.equalsIgnoreCase("create")) {
                return "ERROR: Invalid payload type";
            }

            return "OK";
        }, new JsonTransformer());
    }
}