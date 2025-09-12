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
    protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        String username = req.getPathInfo().substring(1);
        Map<String, Object> model = new HashMap<>();
        model.put("username", username);
        String htmlContent = renderTemplate("hello.html", model);
        resp.setContentType("text/html");
        resp.getWriter().println(htmlContent);
    }

    private String renderTemplate(String templateName, Map<String, Object> model) throws IOException {
        StringBuilder sb = new StringBuilder();
        try (var reader = getClass().getResourceAsStream("/" + templateName)) {
            if (reader == null) throw new IOException("Template not found");
            byte[] buffer = new byte[1024];
            int length;
            while ((length = reader.read(buffer)) != -1) {
                sb.append(new String(buffer, 0, length));
            }
        }
        for (Map.Entry<String, Object> entry : model.entrySet()) {
            sb.replace(0, sb.length(), sb.toString().replace("{{" + entry.getKey() + "}}", entry.getValue().toString()));
        }
        return sb.toString();
    }
}