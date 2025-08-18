import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import org.yaml.snakeyaml.Yaml;

@WebServlet("/receiver")
public class PayloadReceiverServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String payload = request.getParameter("payload");
        
        if (payload == null || payload.isEmpty()) {
            response.setStatus(HttpServletResponse.SC_BAD_REQUEST);
            response.getWriter().println("Error: Missing 'payload' parameter.");
            return;
        }

        Yaml yaml = new Yaml();
        try {
            Object data = yaml.load(payload);
            if (!(data instanceof java.util.Map)) {
                throw new RuntimeException("Payload is not a valid YAML map");
            }
            
            java.util.Map<String, Object> payloadMap = (java.util.Map<String, Object>) data;
            String type = (String) payloadMap.get("type");

            if ("Create".equals(type)) {
                response.setStatus(HttpServletResponse.SC_BAD_REQUEST);
                response.getWriter().println("Error: 'Create' type is not allowed.");
            } else {
                response.getWriter().println("Payload received and processed successfully.");
            }
        } catch (Exception e) {
            response.setStatus(HttpServletResponse.SC_BAD_REQUEST);
            response.getWriter().println("Error: Invalid YAML payload. " + e.getMessage());
        }
    }
}