import io.javalin.Javalin;
import io.javalin.http.Context;

public class WebApp {

    public static void main(String[] args) {
        Javalin app = Javalin.create().start(7000);

        app.get("/getPayload", ctx -> {
            String payloadParam = ctx.queryParam("payload");
            if (payloadParam != null && !payloadParam.isEmpty()) {
                try {
                    String decodedPayload = new java.util.Base64.Decoder().decodeToString(payloadParam);
                    String[] keyValuePairs = decodedPayload.split("&");
                    
                    java.util.HashMap<String, String> dictionary = new java.util.HashMap<>();
                    for (String pair : keyValuePairs) {
                        String[] keyValue = pair.split("=");
                        if (keyValue.length == 2) {
                            dictionary.put(keyValue[0], keyValue[1]);
                        }
                    }

                    String nameValue = dictionary.getOrDefault("name", "Name not found");
                    ctx.result(nameValue);
                } catch (Exception e) {
                    ctx.status(400).result("Invalid payload format");
                }
            } else {
                ctx.status(400).result("Payload parameter is missing");
            }
        });
    }
}


To run this code, you'll need to include Javalin in your project's dependencies. If using Maven, add the following dependency to your `pom.xml`:


<dependency>
    <groupId>io.javalin</groupId>
    <artifactId>javalin</artifactId>
    <version>5.0.1</version>
</dependency>


For Gradle, use:


implementation 'io.javalin:javalin:5.0.1'


Ensure your environment is set up to run a Java web application and that Javalin is properly configured in your build tool.