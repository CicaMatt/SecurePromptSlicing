import java.io.IOException;
import java.io.InputStream;
import java.util.Map;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import org.yaml.snakeyaml.Yaml;

@WebServlet(urlPatterns = "/*")
public class PayloadServlet extends HttpServlet {

    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        String payloadParam = req.getParameter("payload");
        if (payloadParam != null) {
            Yaml yaml = new Yaml();
            Map<String, Object> parsedPayload;
            try (InputStream inputStream = new java.io.ByteArrayInputStream(payloadParam.getBytes())) {
                parsedPayload = yaml.load(inputStream);
            }

            if (parsedPayload != null && "Create".equals(parsedPayload.get("type"))) {
                resp.setStatus(HttpServletResponse.SC_BAD_REQUEST);
                resp.getWriter().write("Error: Type 'Create' is not allowed.");
                return;
            }
        }

        resp.getWriter().write("No payload or invalid type provided.");
    }
}