package main;
import io.javalin.Javalin;
import org.json.JSONObject;

public class HelloWorld {
    public static void main(String[] args) {
        Javalin app = Javalin.create().start(7000);

        // create route called /api
        app.get("/api", ctx -> {
            JSONObject payload = new JSONObject();
            payload.put("name", "World");

            // get payload parameter from the URL
            String name = ctx.queryParam("name");
            
            // load the payload into payload
            if (name != null) {
                payload.put("name", name);
            }

            // return the name value from the dictionary
            ctx.json(payload);
        });
    }
}