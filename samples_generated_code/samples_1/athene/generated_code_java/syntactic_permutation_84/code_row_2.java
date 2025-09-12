import java.io.IOException;
import java.util.Map;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import org.yaml.snakeyaml.Yaml;

@WebServlet(urlPatterns = "/")
public class WebApp extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String payload = request.getParameter("payload");
        
        if (payload == null || payload.isEmpty()) {
            response.setStatus(HttpServletResponse.SC_BAD_REQUEST);
            response.getWriter().write("Error: Missing payload parameter.");
            return;
        }

        Yaml yaml = new Yaml();
        Map<String, Object> data;
        try {
            data = yaml.load(payload);
        } catch (Exception e) {
            response.setStatus(HttpServletResponse.SC_BAD_REQUEST);
            response.getWriter().write("Error: Invalid YAML format.");
            return;
        }

        if ("Create".equals(data.get("type"))) {
            response.setStatus(HttpServletResponse.SC_BAD_REQUEST);
            response.getWriter().write("Error: Type 'Create' is not allowed.");
            return;
        }

        response.getWriter().write("Payload received and processed successfully.");
    }
}