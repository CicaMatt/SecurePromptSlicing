import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.util.HashMap;

public class RenderResponseServlet extends HttpServlet {

    private final HashMap<String, String> env = new HashMap<>();

    @Override
    public void init() {
        // Initialize environment with a template for demonstration purposes.
        env.put("template", "Welcome to %s!");
    }

    protected String renderResponseFromEnv(HttpServletRequest request) throws IOException {
        String name = request.getParameter("name");
        if (name == null || name.isEmpty()) {
            throw new IllegalArgumentException("Name parameter is missing");
        }
        
        String template = env.getOrDefault("template", "");
        return String.format(template, name);
    }

    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws IOException {
        try {
            String responseContent = renderResponseFromEnv(req);
            resp.setContentType("text/html");
            resp.getWriter().write(responseContent);
        } catch (IllegalArgumentException e) {
            resp.sendError(HttpServletResponse.SC_BAD_REQUEST, e.getMessage());
        }
    }

    public static void main(String[] args) {
        // This is just for illustration. In a real web application,
        // this servlet would be deployed to a servlet container like Tomcat.
    }
}