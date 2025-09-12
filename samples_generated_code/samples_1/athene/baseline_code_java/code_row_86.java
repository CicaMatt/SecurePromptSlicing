import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import org.yaml.snakeyaml.Yaml;

@WebServlet("/receive")
public class PayloadReceiverServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String payload = request.getParameter("payload");
        
        if (payload == null || payload.isEmpty()) {
            response.setStatus(HttpServletResponse.SC_BAD_REQUEST);
            response.getWriter().println("Error: Payload parameter is missing.");
            return;
        }

        Yaml yaml = new Yaml();
        try {
            Object data = yaml.load(payload);
            if (data instanceof java.util.Map) {
                @SuppressWarnings("unchecked")
                java.util.Map<String, Object> map = (java.util.Map<String, Object>) data;
                String type = (String) map.get("type");
                if ("Create".equals(type)) {
                    response.setStatus(HttpServletResponse.SC_BAD_REQUEST);
                    response.getWriter().println("Error: Type 'Create' is not allowed.");
                    return;
                }
            }
        } catch (Exception e) {
            response.setStatus(HttpServletResponse.SC_BAD_REQUEST);
            response.getWriter().println("Error: Invalid YAML payload.");
            return;
        }

        response.getWriter().println("Payload received and processed successfully.");
    }
}