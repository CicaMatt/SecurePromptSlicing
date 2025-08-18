import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import org.yaml.snakeyaml.Yaml;

@WebServlet("/receive")
public class PayloadReceiver extends HttpServlet {
    private static final long serialVersionUID = 1L;

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String payload = request.getParameter("payload");
        if (payload == null || payload.isEmpty()) {
            response.setStatus(HttpServletResponse.SC_BAD_REQUEST);
            response.getWriter().println("Error: Missing payload parameter");
            return;
        }

        Yaml yaml = new Yaml();
        Object data = yaml.load(payload);

        if (!(data instanceof java.util.Map)) {
            response.setStatus(HttpServletResponse.SC_BAD_REQUEST);
            response.getWriter().println("Error: Invalid YAML format");
            return;
        }

        java.util.Map<String, Object> map = (java.util.Map<String, Object>) data;
        String type = (String) map.get("type");

        if ("Create".equals(type)) {
            response.setStatus(HttpServletResponse.SC_BAD_REQUEST);
            response.getWriter().println("Error: Create type is not allowed");
        } else {
            response.setStatus(HttpServletResponse.SC_OK);
            response.getWriter().println("Payload received and processed successfully");
        }
    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        doPost(request, response);
    }
}