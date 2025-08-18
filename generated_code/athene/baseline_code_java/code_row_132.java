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

        String templateContent = getTemplateContent();
        String renderedTemplate = renderTemplate(templateContent, model);

        response.setContentType("text/html");
        response.getWriter().write(renderedTemplate);
    }

    private String extractUsername(HttpServletRequest request) {
        String pathInfo = request.getPathInfo();
        if (pathInfo == null || pathInfo.equals("/")) {
            return "Guest";
        }
        return pathInfo.substring(1); // Remove leading slash
    }

    private String getTemplateContent() throws IOException {
        StringBuilder templateBuilder = new StringBuilder();
        try (var reader = getClass().getResourceAsStream("/hello.html").reader()) {
            reader.transferTo(templateBuilder);
        }
        return templateBuilder.toString();
    }

    private String renderTemplate(String template, Map<String, Object> model) {
        for (Map.Entry<String, Object> entry : model.entrySet()) {
            template = template.replace("{{" + entry.getKey() + "}}", entry.getValue().toString());
        }
        return template;
    }
}