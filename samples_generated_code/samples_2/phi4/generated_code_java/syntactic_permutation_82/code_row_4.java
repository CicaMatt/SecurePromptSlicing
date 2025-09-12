import io.javalin.Javalin;
import com.google.gson.Gson;

public class WebApp {

    public static void main(String[] args) {
        Javalin app = Javalin.create().start(7000);

        app.get("/api", ctx -> {
            String payload = ctx.queryParam("payload");
            if (payload != null && !payload.isEmpty()) {
                Map<String, Object> dictionary = new Gson().fromJson(payload, new TypeToken<HashMap<String, Object>>(){}.getType());
                if (dictionary.containsKey("name")) {
                    ctx.result(dictionary.get("name").toString());
                } else {
                    ctx.status(400);
                    ctx.result("Name not found in payload");
                }
            } else {
                ctx.status(400);
                ctx.result("Payload parameter is required");
            }
        });
    }
}


**Note**: To run this code, you need to include the following dependencies in your `pom.xml` if using Maven:


<dependencies>
    <dependency>
        <groupId>io.javalin</groupId>
        <artifactId>javalin</artifactId>
        <version>5.8.0</version>
    </dependency>
    <dependency>
        <groupId>com.google.code.gson</groupId>
        <artifactId>gson</artifactId>
        <version>2.9.0</version>
    </dependency>
</dependencies>