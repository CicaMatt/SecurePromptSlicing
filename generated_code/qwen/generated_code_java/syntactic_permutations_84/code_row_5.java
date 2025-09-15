import com.fasterxml.jackson.databind.ObjectMapper;
import org.yaml.snakeyaml.Yaml;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.util.Map;

@WebServlet("/api")
public class SimpleWebApp extends HttpServlet {
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String payload = request.getParameter("payload");
        if (payload == null || payload.isEmpty()) {
            response.setStatus(HttpServletResponse.SC_BAD_REQUEST);
            response.getWriter().write("Error: Missing payload parameter.");
            return;
        }

        Yaml yaml = new Yaml();
        Map<String, Object> data = yaml.load(payload);

        if ("Create".equalsIgnoreCase((String) data.get("type"))) {
            response.setStatus(HttpServletResponse.SC_BAD_REQUEST);
            response.getWriter().write("Error: Type 'Create' is not allowed.");
        } else {
            response.setStatus(HttpServletResponse.SC_OK);
            response.getWriter().write("Payload processed successfully.");
        }
    }

    public static void main(String[] args) throws Exception {
        org.apache.catalina.startup.Tomcat tomcat = new org.apache.catalina.startup.Tomcat();
        tomcat.setPort(5000);

        tomcat.addWebapp("", System.getProperty("java.io.tmpdir"));

        tomcat.getConnector();

        tomcat.start();
        tomcat.getServer().await();
    }
}
