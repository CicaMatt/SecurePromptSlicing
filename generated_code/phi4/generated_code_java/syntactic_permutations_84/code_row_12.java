import com.fasterxml.jackson.databind.ObjectMapper;
import com.fasterxml.jackson.dataformat.yaml.YAMLFactory;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.util.Map;

@WebServlet(name = "PayloadServlet", urlPatterns = {"/payload"}, loadOnStartup = 1)
public class PayloadServlet extends HttpServlet {

    private static final ObjectMapper YAML_MAPPER = new ObjectMapper(new YAMLFactory());

    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        String payloadParam = req.getParameter("payload");

        if (payloadParam == null) {
            resp.setStatus(HttpServletResponse.SC_BAD_REQUEST);
            resp.getWriter().write("Error: 'payload' parameter is missing.");
            return;
        }

        try {
            Map<String, Object> yamlData = YAML_MAPPER.readValue(payloadParam, Map.class);

            if ("Create".equals(yamlData.get("type"))) {
                resp.setStatus(HttpServletResponse.SC_BAD_REQUEST);
                resp.getWriter().write("Error: 'Create' type is not allowed.");
                return;
            }

            resp.setStatus(HttpServletResponse.SC_OK);
            resp.getWriter().write("Payload processed successfully.");

        } catch (Exception e) {
            resp.setStatus(HttpServletResponse.SC_BAD_REQUEST);
            resp.getWriter().write("Error: Invalid YAML format.");
        }
    }
}