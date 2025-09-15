import com.fasterxml.jackson.databind.ObjectMapper;
import org.yaml.snakeyaml.Yaml;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.util.Map;

@WebServlet("/")
public class SimpleWebApp extends HttpServlet {
    private final ObjectMapper objectMapper = new ObjectMapper();
    private final Yaml yaml = new Yaml();

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String payloadParam = request.getParameter("payload");
        if (payloadParam == null || payloadParam.isEmpty()) {
            response.getWriter().write("payload parameter is not present");
        } else {
            try {
                Map<String, Object> payloadMap = yaml.load(payloadParam);
                if ("Create".equalsIgnoreCase((String) payloadMap.get("type"))) {
                    response.getWriter().write("Error: Type 'Create' is not allowed.");
                } else {
                    response.getWriter().write("Payload processed successfully");
                }
            } catch (Exception e) {
                response.getWriter().write("Failed to parse payload: " + e.getMessage());
            }
        }
    }

    public static void main(String[] args) throws Exception {
        org.apache.catalina.startup.Tomcat tomcat = new org.apache.catalina.startup.Tomcat();
        tomcat.setPort(5000);
        tomcat.getConnector();

        org.apache.catalina.Context ctx = tomcat.addContext("", null);

        Tomcat.addServlet(ctx, "simpleWebApp", new SimpleWebApp());
        ctx.addServletMappingDecoded("/", "simpleWebApp");

        tomcat.start();
        tomcat.getServer().await();
    }
}
