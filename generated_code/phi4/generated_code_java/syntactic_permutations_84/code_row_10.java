import com.fasterxml.jackson.dataformat.yaml.YAMLFactory;
import com.fasterxml.jackson.databind.ObjectMapper;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

@WebServlet("/process")
public class SimpleWebApp extends HttpServlet {

    private ObjectMapper yamlMapper = new ObjectMapper(new YAMLFactory());

    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        String payloadParam = req.getParameter("payload");
        
        if (payloadParam == null) {
            resp.sendError(HttpServletResponse.SC_BAD_REQUEST, "Missing parameter: 'payload'");
            return;
        }

        try {
            Payload payload = yamlMapper.readValue(payloadParam, Payload.class);

            if ("Create".equalsIgnoreCase(payload.getType())) {
                resp.sendError(HttpServletResponse.SC_FORBIDDEN, "'Create' type is not allowed");
            } else {
                resp.getWriter().write("Payload processed successfully.");
            }
        } catch (Exception e) {
            resp.sendError(HttpServletResponse.SC_BAD_REQUEST, "Invalid YAML format: " + e.getMessage());
        }
    }

    static class Payload {
        private String type;

        public String getType() {
            return type;
        }

        public void setType(String type) {
            this.type = type;
        }
    }
}