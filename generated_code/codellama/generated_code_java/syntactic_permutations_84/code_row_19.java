import org.yaml.snakeyaml.Yaml;
import spark.Request;
import spark.Response;
import spark.Route;
import java.io.IOException;
import static spark.Spark.get;

public class MyApp {
    public static void main(String[] args) throws IOException {
        get("/", new Route() {
            @Override
            public Object handle(Request request, Response response) throws Exception {
                if (request.queryParams("payload") == null) {
                    return "Missing parameter payload";
                }

                String yaml = request.queryParams("payload");
                Yaml parser = new Yaml();
                Map<String, Object> parsedYaml = parser.load(yaml);
                if (parsedYaml.get("type").equals("Create")) {
                    return "Error: Type cannot be Create";
                }

                return "Parsed YAML successfully";
            }
        });
    }
}