import com.fasterxml.jackson.databind.ObjectMapper;
import com.fasterxml.jackson.dataformat.yaml.YAMLFactory;
import io.javalin.Javalin;

public class SimpleWebApp {

    public static void main(String[] args) {
        Javalin app = Javalin.create(config -> {
            config.defaultContentType = "application/json";
        }).start(5000);

        app.get("/", ctx -> {
            String payloadParam = ctx.queryParam("payload");
            
            if (payloadParam == null || payloadParam.isEmpty()) {
                ctx.status(400);
                ctx.result("{\"error\":\"Payload parameter is missing\"}");
            } else {
                try {
                    ObjectMapper yamlMapper = new ObjectMapper(new YAMLFactory());
                    Payload payload = yamlMapper.readValue(payloadParam, Payload.class);

                    if ("Create".equals(payload.getType())) {
                        ctx.status(400);
                        ctx.result("{\"error\":\"Type cannot be Create\"}");
                    } else {
                        ctx.result("{\"message\":\"Request processed successfully\"}");
                    }
                } catch (Exception e) {
                    ctx.status(400);
                    ctx.result("{\"error\":\"Invalid YAML payload\"}");
                }
            }
        });

        static class Payload {
            private String type;

            public String getType() {
                return type;
            }

            public void setType(String type) {
                this.type = type;
            }
        }
    }
}


Dependencies (in `pom.xml` for Maven):


<dependencies>
    <dependency>
        <groupId>io.javalin</groupId>
        <artifactId>javalin</artifactId>
        <version>4.15.0</version>
    </dependency>
    <dependency>
        <groupId>com.fasterxml.jackson.core</groupId>
        <artifactId>jackson-databind</artifactId>
        <version>2.14.1</version>
    </dependency>
    <dependency>
        <groupId>com.fasterxml.jackson.dataformat</groupId>
        <artifactId>jackson-dataformat-yaml</artifactId>
        <version>2.14.1</version>
    </dependency>
</dependencies>