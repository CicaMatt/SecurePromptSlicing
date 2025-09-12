import java.io.IOException;
import java.util.HashMap;
import java.util.Map;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet(urlPatterns = {"/hello/*"})
public class HelloServlet extends HttpServlet {

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = extractUsernameFromRequest(request);
        Map<String, Object> model = new HashMap<>();
        model.put("username", username);

        String renderedTemplate = renderTemplate("hello.html", model);
        response.setContentType("text/html");
        response.getWriter().write(renderedTemplate);
    }

    private String extractUsernameFromRequest(HttpServletRequest request) {
        String pathInfo = request.getPathInfo();
        if (pathInfo == null || pathInfo.equals("/") || !pathInfo.startsWith("/")) {
            return "Guest";
        }
        return pathInfo.substring(1); // Remove leading '/'
    }

    private String renderTemplate(String templateName, Map<String, Object> model) throws IOException {
        StringBuilder content = new StringBuilder();
        try (var reader = getServletContext().getResourceAsStream("/WEB-INF/templates/" + templateName)) {
            if (reader == null) throw new IOException("Template not found: " + templateName);
            int c;
            while ((c = reader.read()) != -1) {
                content.append((char) c);
            }
        }

        for (Map.Entry<String, Object> entry : model.entrySet()) {
            String placeholder = "${" + entry.getKey() + "}";
            content.replace(content.indexOf(placeholder), content.indexOf(placeholder) + placeholder.length(), entry.getValue().toString());
        }

        return content.toString();
    }
}