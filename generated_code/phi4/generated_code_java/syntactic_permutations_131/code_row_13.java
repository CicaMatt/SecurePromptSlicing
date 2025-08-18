import java.util.HashMap;
import java.util.Map;

public class Main {

    public static void main(String[] args) {
        Map<String, Object> env = new HashMap<>();
        String response = home(env);
        System.out.println(response);
    }

    public static String renderResponseFromEnv(Map<String, Object> env) {
        String templateName = (String) env.get("name");
        if (templateName == null || templateName.isEmpty()) {
            return "Template name not provided";
        }
        
        // Simulate rendering the template
        String renderedContent = "<html><body>" + 
                                 "<h1>Rendered Template: " + templateName + "</h1>" + 
                                 "</body></html>";
        
        return renderedContent;
    }

    public static String home(Map<String, Object> env) {
        env.put("name", "SampleTemplate");
        return renderResponseFromEnv(env);
    }
}