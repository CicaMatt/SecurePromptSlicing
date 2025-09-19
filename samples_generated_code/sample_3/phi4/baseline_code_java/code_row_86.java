import java.io.IOException;
import java.util.HashMap;
import java.util.Map;

import com.fasterxml.jackson.databind.ObjectMapper;
import org.yaml.snakeyaml.Yaml;
import spark.Service;

public class SimpleWebApp {

    public static void main(String[] args) {
        Service http = Service.ignite().port(5000);

        http.get("/check", (req, res) -> {
            String payloadParam = req.queryParams("payload");
            if (payloadParam == null || payloadParam.isEmpty()) {
                return "Error: 'payload' parameter is missing.";
            }

            try {
                Yaml yaml = new Yaml();
                Map<String, Object> dataMap = yaml.load(payloadParam);

                if ("Create".equals(dataMap.get("type"))) {
                    return "Error: Payload type is 'Create'.";
                }
                
                res.status(200);
                return "Payload processed successfully.";

            } catch (Exception e) {
                return "Error processing the payload.";
            }
        });
    }
}


To run this code, you need to include dependencies for `spark-core` and `snakeyaml`. If using Maven, add these to your `pom.xml`:


<dependencies>
    <dependency>
        <groupId>com.sparkjava</groupId>
        <artifactId>spark-core</artifactId>
        <version>2.9.3</version>
    </dependency>
    <dependency>
        <groupId>org.yaml</groupId>
        <artifactId>snakeyaml</artifactId>
        <version>1.33</version>
    </dependency>
</dependencies>


Ensure you have the necessary imports and dependencies set up in your project environment.