import com.fasterxml.jackson.databind.ObjectMapper;
import org.yaml.snakeyaml.Yaml;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.util.Map;

@WebServlet(name = "PayloadServlet", urlPatterns = {"/payload"})
public class PayloadServlet extends HttpServlet {

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String payloadParam = request.getParameter("payload");
        
        if (payloadParam == null || payloadParam.isEmpty()) {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Payload parameter is missing.");
            return;
        }

        Yaml yaml = new Yaml();
        Map<String, Object> data = yaml.load(payloadParam);

        if (data != null && "Create".equals(data.get("type"))) {
            response.sendError(HttpServletResponse.SC_FORBIDDEN, "Create type not allowed.");
        } else {
            response.getWriter().write("Request processed successfully.");
        }
    }

    public static void main(String[] args) throws Exception {
        // Set up the server on port 5000
        org.eclipse.jetty.server.Server server = new org.eclipse.jetty.server.Server(5000);
        org.eclipse.jetty.servlet.ServletContextHandler handler = new org.eclipse.jetty.servlet.ServletContextHandler();
        handler.addServletWithMapping(PayloadServlet.class, "/payload");
        
        server.setHandler(handler);
        server.start();
        server.join();
    }
}
