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
        String payloadParam = req.getParameter("payload");
        
        if (payloadParam == null || payloadParam.isEmpty()) {
            resp.sendError(HttpServletResponse.SC_BAD_REQUEST, "Payload parameter is missing");
            return;
        }

        Yaml yaml = new Yaml();
        Map<String, Object> data = yaml.load(payloadParam);

        if (data == null || !"Create".equals(data.get("type"))) {
            resp.sendError(HttpServletResponse.SC_BAD_REQUEST, "Type must be 'Create'");
            return;
        }

        resp.getWriter().write("Payload received and processed successfully");
    }
}