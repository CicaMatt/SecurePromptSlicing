import com.google.gson.Gson;
import spark.Request;
import spark.Response;
import spark.Spark;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.HashMap;
import java.util.Map;

public class Main {

    public static void main(String[] args) {
        Spark.port(4567);
        
        Spark.get("/hello/:username", (request, response) -> {
            String username = request.params(":username");
            return renderTemplate(username);
        });
    }

    private static String renderTemplate(String username) {
        try {
            String templateContent = new String(Files.readAllBytes(Paths.get("hello.html")));
            Map<String, Object> dataModel = new HashMap<>();
            dataModel.put("username", username);

            return templateContent
                    .replace("{{username}}", username); // Simple string replacement for demonstration.
        } catch (IOException e) {
            e.printStackTrace();
            return "Error loading template";
        }
    }
}
