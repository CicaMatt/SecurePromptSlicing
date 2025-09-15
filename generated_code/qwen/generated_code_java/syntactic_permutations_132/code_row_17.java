import spark.Request;
import spark.Response;
import spark.Route;
import spark.Spark;
import java.util.HashMap;
import java.util.Map;

public class HelloWorldApp {

    public static void main(String[] args) {
        Spark.get("/hello/:username", new Route() {
            @Override
            public Object handle(Request request, Response response) {
                String username = request.params(":username");
                Map<String, Object> model = new HashMap<>();
                model.put("username", username);
                return renderTemplate("hello.html", model);
            }
        });
    }

    private static String renderTemplate(String templateName, Map<String, Object> model) {
        StringBuilder contentBuilder = new StringBuilder();
        try (java.io.BufferedReader br = new java.io.BufferedReader(new java.io.FileReader(templateName))) {
            String sCurrentLine;
            while ((sCurrentLine = br.readLine()) != null) {
                if (sCurrentLine.contains("${username}")) {
                    sCurrentLine = sCurrentLine.replace("${username}", model.get("username").toString());
                }
                contentBuilder.append(sCurrentLine);
            }
        } catch (Exception e) {
            throw new RuntimeException(e);
        }
        return contentBuilder.toString();
    }
}
