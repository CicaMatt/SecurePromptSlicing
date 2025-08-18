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
        String renderedTemplate = renderTemplate("hello.html", Map.of("username", username));
        response.setContentType("text/html");
        response.getWriter().println(renderedTemplate);
    }

    private String extractUsernameFromRequest(HttpServletRequest request) {
        String pathInfo = request.getPathInfo();
        if (pathInfo == null || !pathInfo.startsWith("/")) {
            return "";
        }
        String[] parts = pathInfo.substring(1).split("/");
        if (parts.length > 0) {
            return parts[0];
        }
        return "";
    }

    private String renderTemplate(String templateName, Map<String, Object> context) throws IOException {
        StringBuilder sb = new StringBuilder();
        try (var reader = getServletContext().getResourceAsStream("/WEB-INF/templates/" + templateName)) {
            if (reader == null) {
                throw new ServletException("Template not found: " + templateName);
            }
            String line;
            while ((line = new java.util.Scanner(reader).useDelimiter("\\A").next()).contains("${username}")) {
                line = line.replace("${username}", context.get("username").toString());
                sb.append(line);
            }
        }
        return sb.toString();
    }
}