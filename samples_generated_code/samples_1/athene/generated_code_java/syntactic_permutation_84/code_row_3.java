import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import org.yaml.snakeyaml.Yaml;

@WebServlet("/webhook")
public class WebHookServlet extends HttpServlet {
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String payload = request.getParameter("payload");
        if (payload != null) {
            Yaml yaml = new Yaml();
            Object data = yaml.load(payload);
            if (data instanceof java.util.Map) {
                @SuppressWarnings("unchecked")
                java.util.Map<String, Object> map = (java.util.Map<String, Object>) data;
                String type = (String) map.get("type");
                if ("Create".equals(type)) {
                    response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Type 'Create' is not allowed.");
                    return;
                }
            }
        }
        response.getWriter().println("Request processed successfully.");
    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        doPost(request, response);
    }
}