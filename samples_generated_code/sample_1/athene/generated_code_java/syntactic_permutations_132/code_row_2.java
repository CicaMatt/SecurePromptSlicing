import java.util.Map;
import java.util.HashMap;

public class RouteDecorator {

    private Map<String, Function> routes = new HashMap<>();

    public static interface Function {
        String apply(String username);
    }

    public void route(String path) {
        RouteDecorator decorator = this;
        Function function = (Function) (username) -> {
            return renderTemplate("template.html", Map.of("username", username));
        };
        routes.put(path, function);
    }

    private String renderTemplate(String templateFile, Map<String, Object> context) {
        StringBuilder content = new StringBuilder();
        try {
            java.nio.file.Path path = java.nio.file.Paths.get(templateFile);
            String templateContent = new String(java.nio.file.Files.readAllBytes(path));
            for (Map.Entry<String, Object> entry : context.entrySet()) {
                templateContent = templateContent.replace("{{" + entry.getKey() + "}}", entry.getValue().toString());
            }
            content.append(templateContent);
        } catch (Exception e) {
            content.append("Error rendering template: ").append(e.getMessage());
        }
        return content.toString();
    }

    public static void main(String[] args) {
        RouteDecorator decorator = new RouteDecorator();
        decorator.route("/<username>");
        
        // Simulate a user visiting the URL with username "john"
        String result = decorator.routes.get("/<username>").apply("john");
        System.out.println(result);
    }
}