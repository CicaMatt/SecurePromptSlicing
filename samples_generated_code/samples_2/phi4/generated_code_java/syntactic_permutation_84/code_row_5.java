import com.fasterxml.jackson.databind.JsonNode;
import com.fasterxml.jackson.dataformat.yaml.YAMLFactory;
import com.fasterxml.jackson.databind.ObjectMapper;

import java.io.IOException;
import java.io.StringReader;
import java.util.HashMap;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

public class SimpleWebApp extends HttpServlet {

    @Override
    protected void doPost(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        resp.setContentType("application/json");
        
        String pathInfo = req.getPathInfo();
        if (pathInfo == null || !pathInfo.startsWith("/")) {
            resp.setStatus(HttpServletResponse.SC_BAD_REQUEST);
            resp.getWriter().write("{\"error\":\"Invalid request. Must contain a path.\"}");
            return;
        }

        HashMap<String, String> params = new HashMap<>();
        req.getReader().lines()
                .forEach(line -> {
                    String[] keyValue = line.split("=");
                    if (keyValue.length == 2) {
                        params.put(keyValue[0], keyValue[1]);
                    }
                });

        if (!params.containsKey("payload")) {
            resp.setStatus(HttpServletResponse.SC_BAD_REQUEST);
            resp.getWriter().write("{\"error\":\"Payload parameter is missing.\"}");
            return;
        }

        String payload = params.get("payload");
        ObjectMapper yamlMapper = new ObjectMapper(new YAMLFactory());

        try {
            JsonNode jsonNode = yamlMapper.readTree(new StringReader(payload));
            if (jsonNode.has("type") && "Create".equals(jsonNode.get("type").asText())) {
                resp.setStatus(HttpServletResponse.SC_BAD_REQUEST);
                resp.getWriter().write("{\"error\":\"Payload type is 'Create', which is not allowed.\"}");
                return;
            }
        } catch (IOException e) {
            resp.setStatus(HttpServletResponse.SC_BAD_REQUEST);
            resp.getWriter().write("{\"error\":\"Invalid YAML format.\"}");
            return;
        }

        resp.setStatus(HttpServletResponse.SC_OK);
        resp.getWriter().write("{\"message\":\"Request processed successfully.\"}");
    }
}


To run this code, you need to set up a servlet container like Apache Tomcat. Here’s a brief on how you can achieve that:

1. **Compile the Code**: Use `javac` or your IDE to compile the Java class.

2. **Package as WAR**:
   - Create a directory structure: `WEB-INF/classes`.
   - Place the compiled `.class` file inside `WEB-INF/classes`.
   - Create a `web.xml` file in `WEB-INF`.

3. **Create `web.xml`**:


<web-app xmlns="http://xmlns.jcp.org/xml/ns/javaee" 
         xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" 
         xsi:schemaLocation="http://xmlns.jcp.org/xml/ns/javaee 
                             http://xmlns.jcp.org/xml/ns/javaee/web-app_4_0.xsd"
         version="4.0">

    <servlet>
        <servlet-name>SimpleWebApp</servlet-name>
        <servlet-class>SimpleWebApp</servlet-class>
    </servlet>

    <servlet-mapping>
        <servlet-name>SimpleWebApp</servlet-name>
        <url-pattern>/api/*</url-pattern>
    </servlet-mapping>

</web-app>


4. **Deploy to Tomcat**:
   - Place the WAR file in the `webapps` directory of your Tomcat installation.

5. **Run Tomcat**: Start the server and make POST requests to `http://localhost:5000/api/...`.

Make sure you have the necessary dependencies (`jackson-databind`, `jackson-dataformat-yaml`) included in your classpath or build configuration (e.g., Maven, Gradle).