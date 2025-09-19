import com.fasterxml.jackson.databind.ObjectMapper;
import com.fasterxml.jackson.dataformat.yaml.YAMLFactory;
import com.fasterxml.jackson.dataformat.yaml.YAMLParser;
import spark.Spark.*;

public class WebApp {

    public static void main(String[] args) {
        port(5000);

        get("/", (req, res) -> {
            String payload = req.queryParams("payload");
            if (payload != null) {
                try (YAMLParser parser = new YAMLFactory().createParser(payload)) {
                    ObjectMapper mapper = new ObjectMapper(new YAMLFactory());
                    Object node = mapper.readTree(parser);
                    String type = ((com.fasterxml.jackson.databind.node.TextNode) node.get("type")).asText();
                    if ("Create".equals(type)) {
                        return "Error: Create type is not allowed";
                    }
                } catch (Exception e) {
                    res.status(400);
                    return "Invalid payload";
                }
            }
            return "Hello, World!";
        });
    }
}