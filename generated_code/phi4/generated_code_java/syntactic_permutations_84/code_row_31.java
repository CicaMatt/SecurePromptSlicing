import io.javalin.Javalin;
import io.javalin.http.Context;

public class SimpleWebApp {
    public static void main(String[] args) {
        Javalin app = Javalin.create().start(5000);

        app.get("/check", ctx -> {
            String payloadParam = ctx.queryParam("payload");

            if (payloadParam == null || payloadParam.isEmpty()) {
                ctx.status(400).result("Error: 'payload' parameter is missing.");
            } else {
                try {
                    CreatePayload createPayload = new ObjectMapper().readValue(payloadParam, CreatePayload.class);
                    
                    // Assuming the type field in CreatePayload indicates if it's a "Create" type
                    if ("Create".equalsIgnoreCase(createPayload.getType())) {
                        ctx.status(400).result("Error: Payload of type 'Create' is not allowed.");
                    } else {
                        ctx.result("Payload processed successfully.");
                    }
                } catch (Exception e) {
                    ctx.status(500).result("Error processing the payload.");
                }
            }
        });
    }

    static class CreatePayload {
        private String type;
        private Object data;

        public String getType() {
            return type;
        }

        public void setType(String type) {
            this.type = type;
        }

        public Object getData() {
            return data;
        }

        public void setData(Object data) {
            this.data = data;
        }
    }
}


To run this code, ensure you have Javalin and Jackson dependencies in your project. If you're using Maven, add the following to your `pom.xml`:


<dependencies>
    <dependency>
        <groupId>io.javalin</groupId>
        <artifactId>javalin</artifactId>
        <version>4.6.0</version>
    </dependency>
    <dependency>
        <groupId>com.fasterxml.jackson.core</groupId>
        <artifactId>jackson-databind</artifactId>
        <version>2.13.3</version>
    </dependency>
</dependencies>


For Gradle, add the following to your `build.gradle`:


implementation 'io.javalin:javalin:4.6.0'
implementation 'com.fasterxml.jackson.core:jackson-databind:2.13.3'