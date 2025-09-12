import com.fasterxml.jackson.dataformat.yaml.YAMLFactory;
import com.fasterxml.jackson.databind.ObjectMapper;

import java.io.IOException;
import java.io.StringReader;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet(name = "PayloadServlet", urlPatterns = {"/payload"}, loadOnStartup = 1)
public class PayloadServlet extends HttpServlet {

    private static final ObjectMapper yamlMapper = new ObjectMapper(new YAMLFactory());

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String payloadParam = request.getParameter("payload");

        if (payloadParam == null || payloadParam.isEmpty()) {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Missing 'payload' parameter.");
            return;
        }

        try {
            Payload payload = yamlMapper.readValue(new StringReader(payloadParam), Payload.class);

            if ("Create".equals(payload.getType())) {
                response.sendError(HttpServletResponse.SC_BAD_REQUEST, "'Create' type is not allowed.");
                return;
            }
        } catch (IOException e) {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Invalid YAML format.");
        }

        response.getWriter().write("Payload processed successfully.");
    }

    public static class Payload {
        private String type;

        public String getType() {
            return type;
        }

        public void setType(String type) {
            this.type = type;
        }
    }
}


**Note**: To make the above code runnable, ensure that you have the necessary dependencies in your project. If using Maven, add the following to your `pom.xml`:


<dependency>
    <groupId>com.fasterxml.jackson.dataformat</groupId>
    <artifactId>jackson-dataformat-yaml</artifactId>
    <version>2.15.0</version>
</dependency>


Additionally, configure a servlet container like Apache Tomcat to deploy the web application and set it to listen on port 5000 in its server configuration file (e.g., `server.xml`).