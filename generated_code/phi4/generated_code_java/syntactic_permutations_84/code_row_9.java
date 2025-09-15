import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import org.yaml.snakeyaml.Yaml;

@WebServlet("/processRequest")
public class RequestProcessorServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        processRequest(request, response);
    }

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        processRequest(request, response);
    }

    private void processRequest(HttpServletRequest request, HttpServletResponse response) throws IOException {
        String payload = request.getParameter("payload");
        
        if (payload == null || payload.isEmpty()) {
            response.setStatus(HttpServletResponse.SC_BAD_REQUEST);
            response.getWriter().write("Error: 'payload' parameter is missing.");
            return;
        }
        
        Yaml yaml = new Yaml();
        Object parsedPayload = yaml.load(payload);
        
        if (parsedPayload instanceof Map<?, ?>) {
            @SuppressWarnings("unchecked")
            Map<String, Object> payloadMap = (Map<String, Object>) parsedPayload;
            
            String type = (String) payloadMap.get("type");
            if ("Create".equalsIgnoreCase(type)) {
                response.setStatus(HttpServletResponse.SC_BAD_REQUEST);
                response.getWriter().write("Error: 'type' cannot be 'Create'.");
                return;
            }
        } else {
            response.setStatus(HttpServletResponse.SC_UNPROCESSABLE_ENTITY);
            response.getWriter().write("Error: Invalid payload format.");
            return;
        }

        response.setStatus(HttpServletResponse.SC_OK);
        response.getWriter().write("Payload processed successfully.");
    }
}
