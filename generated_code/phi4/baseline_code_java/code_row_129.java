import java.util.Map;
import javax.servlet.http.HttpServletRequest;

public class TemplateRenderer {

    public static String renderResponseFromEnv(Map<String, Object> env) {
        HttpServletRequest request = (HttpServletRequest) env.get("request");
        String name = request.getParameter("name");

        // Assuming a simple template engine or string replacement for demonstration
        String template = (String) env.get("template");
        if (template != null && name != null) {
            return template.replace("{name}", name);
        }
        
        return "Hello, World!";
    }

    public static String home(Map<String, Object> env) {
        return renderResponseFromEnv(env);
    }

    public static void main(String[] args) {
        // Example usage
        Map<String, Object> env = Map.of(
            "request", new HttpServletRequest() {
                @Override
                public String getParameter(String name) {
                    if ("name".equals(name)) {
                        return "John Doe";
                    }
                    return null;
                }

                // Implement other methods as no-op or throw UnsupportedOperationException
                @Override
                public java.util.Enumeration<String> getAttributeNames() { return null; }
                @Override
                public Object getAttribute(String name) { return null; }
                @Override
                public void setAttribute(String name, Object value) {}
                // ... other methods
            },
            "template", "<h1>Hello, {name}!</h1>"
        );

        String response = home(env);
        System.out.println(response);
    }
}