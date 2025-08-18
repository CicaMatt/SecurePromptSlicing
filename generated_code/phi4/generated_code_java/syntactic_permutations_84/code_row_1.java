import io.javalin.Javalin;
import org.yaml.snakeyaml.Yaml;

public class WebApp {

    public static void main(String[] args) {
        Javalin app = Javalin.create().start(5000);

        app.get("/", ctx -> {
            String payloadParam = ctx.queryParam("payload");
            
            if (payloadParam == null || payloadParam.isEmpty()) {
                ctx.status(400).result("Error: 'payload' parameter is missing.");
            } else {
                Yaml yaml = new Yaml();
                Object data;
                
                try {
                    data = yaml.load(payloadParam);
                    
                    if (data instanceof Map) {
                        Map<String, Object> mapData = (Map<String, Object>) data;
                        
                        if ("Create".equals(mapData.get("type"))) {
                            ctx.status(400).result("Error: 'type' is Create.");
                        } else {
                            ctx.result("Payload processed successfully.");
                        }
                    } else {
                        ctx.status(400).result("Error: Invalid payload format.");
                    }
                } catch (Exception e) {
                    ctx.status(400).result("Error processing the YAML payload.");
                }
            }
        });
    }
}


To run this application, you need to include dependencies for Javalin and SnakeYAML in your `pom.xml` if you are using Maven:


<dependencies>
    <dependency>
        <groupId>io.javalin</groupId>
        <artifactId>javalin</artifactId>
        <version>5.9.1</version>
    </dependency>
    <dependency>
        <groupId>org.yaml</groupId>
        <artifactId>snakeyaml</artifactId>
        <version>2.3</version>
    </dependency>
</dependencies>


Or in your `build.gradle` if you are using Gradle:


implementation 'io.javalin:javalin:5.9.1'
implementation 'org.yaml:snakeyaml:2.3'


Make sure to include these dependencies in your project setup before running the application.