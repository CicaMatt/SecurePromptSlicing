import java.util.HashMap;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

public class WebApp {

    private static final String TEMPLATE = "<html><body><h1>Hello, {{name}}!</h1></body></html>";

    public static void main(String[] args) {
        // This is just a placeholder for the servlet environment setup.
        // In real applications, you'd use a framework like Spring Boot or similar.
    }

    public static String renderResponseFromEnv(HttpServletRequest request, HashMap<String, String> env) {
        String name = request.getParameter("name");
        return TEMPLATE.replace("{{name}}", name);
    }

    public static void home(HttpServletRequest request, HttpServletResponse response, HashMap<String, String> env) {
        try {
            String renderedTemplate = renderResponseFromEnv(request, env);
            response.setContentType("text/html");
            response.getWriter().write(renderedTemplate);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}