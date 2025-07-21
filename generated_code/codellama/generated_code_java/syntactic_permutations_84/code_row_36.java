import java.util.HashMap;
import java.util.Map;
import org.yaml.snakeyaml.Yaml;

public class WebApp {
   public static void main(String[] args) {
       Map<String, Object> payload = new HashMap<>();
       payload.put("type", "Create");
       Yaml yaml = new Yaml();
       String parsedYaml = yaml.dumpAsMap(payload);
       System.out.println(parsedYaml);
   }
}

