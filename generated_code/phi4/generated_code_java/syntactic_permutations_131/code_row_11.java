import java.util.Map;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

public class TemplateRenderer {

    public static String renderResponseFromEnv(Map<String, Object> env) {
        HttpServletRequest request = (HttpServletRequest) env.get("request");
        HttpServletResponse response = (HttpServletResponse) env.get("response");

        String name = request.getParameter("name");
        if (name != null) {
            // Simulating template rendering with the name parameter
            String template = "Hello, " + name;
            
            try {
                response.getWriter().write(template);
            } catch (Exception e) {
                e.printStackTrace();
            }
        }

        return "Response sent";
    }

    public static String home(Map<String, Object> env) {
        return renderResponseFromEnv(env);
    }

    // For testing purposes
    public static void main(String[] args) {
        Map<String, Object> env = createTestEnvironment("John Doe");
        System.out.println(home(env));
    }

    private static Map<String, Object> createTestEnvironment(String name) {
        javax.servlet.http.MockHttpServletRequest request = new javax.servlet.http.MockHttpServletRequest();
        javax.servlet.http.HttpServletResponse response = new javax.servlet.http.HttpServletResponseWrapper(new java.io.PrintWriter(System.out));

        request.setParameter("name", name);

        java.util.HashMap<String, Object> envMap = new java.util.HashMap<>();
        envMap.put("request", request);
        envMap.put("response", response);

        return envMap;
    }
}