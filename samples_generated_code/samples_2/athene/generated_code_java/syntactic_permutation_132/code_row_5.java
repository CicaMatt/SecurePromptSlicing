import java.io.IOException;
import java.util.HashMap;
import java.util.Map;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/hello/*")
public class HelloServlet extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = extractUsername(request);
        Map<String, Object> model = new HashMap<>();
        model.put("username", username);
        String renderedTemplate = renderTemplate("hello.html", model);
        response.setContentType("text/html");
        response.getWriter().println(renderedTemplate);
    }

    private String extractUsername(HttpServletRequest request) {
        String pathInfo = request.getPathInfo();
        if (pathInfo == null || pathInfo.equals("/")) {
            return "Guest";
        }
        return pathInfo.substring(1); // Remove leading '/'
    }

    private String renderTemplate(String templateName, Map<String, Object> model) throws IOException {
        StringBuilder sb = new StringBuilder();
        try (var reader = getServletContext().getResourceAsStream("/WEB-INF/templates/" + templateName)) {
            if (reader == null) {
                throw new IOException("Template not found");
            }
            int c;
            while ((c = reader.read()) != -1) {
                sb.append((char) c);
            }
        }

        String template = sb.toString();
        for (Map.Entry<String, Object> entry : model.entrySet()) {
            template = template.replace("{{" + entry.getKey() + "}}", entry.getValue().toString());
        }
        return template;
    }
}