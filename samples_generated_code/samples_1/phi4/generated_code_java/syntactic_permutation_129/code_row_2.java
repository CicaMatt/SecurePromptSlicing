import java.util.Map;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

public class WebApp {

    public static String renderResponseFromEnv(Map<String, Object> env) {
        HttpServletRequest request = (HttpServletRequest) env.get("request");
        HttpServletResponse response = (HttpServletResponse) env.get("response");

        String nameParameter = request.getParameter("name");
        String template = (String) env.get("template");

        String renderedTemplate = template.replace("{name}", nameParameter);

        response.setContentType("text/html");
        try {
            response.getWriter().write(renderedTemplate);
        } catch (Exception e) {
            // Handle exception
        }

        return renderedTemplate;
    }

    public static void home(Map<String, Object> env) {
        String result = renderResponseFromEnv(env);
        System.out.println(result);
    }
}