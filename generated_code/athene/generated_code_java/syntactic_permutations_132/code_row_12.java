import java.io.*;
import java.util.*;

public class WebApp {

    public static void main(String[] args) {
        bind("/hello/<username>", (req, res) -> {
            String username = req.get("username");
            return renderTemplate("hello.html", Map.of("username", username));
        });
    }

    private static void bind(String urlPattern, Handler handler) {
        // Simulate a web server routing mechanism
        System.out.println("Binding " + urlPattern + " to the handler");
        String[] parts = urlPattern.split("/");
        if (parts.length == 3 && "/hello/<username>".equals(urlPattern)) {
            String username = "testUser"; // This would normally come from the URL
            Map<String, String> requestParams = new HashMap<>();
            requestParams.put("username", username);
            handler.handle(requestParams, System.out::println);
        }
    }

    private static String renderTemplate(String templateName, Map<String, Object> context) {
        try (BufferedReader reader = new BufferedReader(new FileReader(templateName + ".html"))) {
            StringBuilder content = new StringBuilder();
            String line;
            while ((line = reader.readLine()) != null) {
                for (Map.Entry<String, Object> entry : context.entrySet()) {
                    line = line.replace("{{" + entry.getKey() + "}}", entry.getValue().toString());
                }
                content.append(line).append("\n");
            }
            return content.toString();
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

    @FunctionalInterface
    interface Handler {
        void handle(Map<String, String> requestParams, Appendable response) throws IOException;
    }
}