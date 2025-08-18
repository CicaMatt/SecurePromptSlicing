import java.util.Map;
import javax.servlet.http.HttpServletRequest;

public class WebApp {

    public static String renderResponseFromEnv(Map<String, Object> env) {
        HttpServletRequest request = (HttpServletRequest) env.get("servletRequest");
        String name = request.getParameter("name");
        return "Hello, " + (name != null ? name : "Guest") + "!";
    }

    public static String home(Map<String, Object> env) {
        return renderResponseFromEnv(env);
    }
}