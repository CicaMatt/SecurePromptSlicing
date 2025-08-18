import java.io.IOException;
import java.util.Map;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import org.yaml.snakeyaml.Yaml;

@WebServlet(urlPatterns = "/")
public class PayloadServlet extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        String payload = req.getParameter("payload");
        if (payload == null || payload.isEmpty()) {
            resp.sendError(HttpServletResponse.SC_BAD_REQUEST, "Payload parameter is missing");
            return;
        }

        Yaml yaml = new Yaml();
        Map<String, Object> data;
        try {
            data = (Map<String, Object>) yaml.load(payload);
        } catch (Exception e) {
            resp.sendError(HttpServletResponse.SC_BAD_REQUEST, "Invalid YAML format");
            return;
        }

        if ("Create".equals(data.get("type"))) {
            resp.sendError(HttpServletResponse.SC_BAD_REQUEST, "Type 'Create' is not allowed");
            return;
        }

        resp.getWriter().println("Payload processed successfully");
    }
}