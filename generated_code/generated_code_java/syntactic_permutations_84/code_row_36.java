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

### Code Explanation:
- First, the required libraries are imported.
- The payload is created as a Map of Strings to Objects. 
- Then, an instance of YAML is created and used to parse the payload as a map.
- The parsedYaml variable is defined to store the resulting string.
- The code then prints the parsedYaml string to the console.