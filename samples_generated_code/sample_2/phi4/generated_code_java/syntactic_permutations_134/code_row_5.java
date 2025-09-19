import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import java.util.HashMap;
import java.util.Map;

public class HelloServlet extends HttpServlet {

    private Map<String, String> urlMappings = new HashMap<>();

    public void init() {
        // Mapping URLs to actions
        urlMappings.put("/hello/", this::sayHello);
        // Add more mappings as needed
    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String path = request.getPathInfo();
        
        if (path != null && urlMappings.containsKey(path)) {
            try {
                urlMappings.get(path).invoke(this, request, response);
            } catch (Exception e) {
                e.printStackTrace(response.getWriter());
            }
        } else {
            response.sendError(HttpServletResponse.SC_NOT_FOUND, "Not Found");
        }
    }

    private void sayHello(HttpServletRequest req, HttpServletResponse res) throws IOException {
        String username = req.getPathInfo().substring(7); // Remove "/hello/" part
        if (username == null || username.isEmpty()) {
            username = "world";
        }
        
        String message = "Hello " + escape(username);
        response.setContentType("text/plain");
        response.getWriter().write(message);
    }

    private String escape(String input) {
        return input.replace("&", "&amp;")
                    .replace("<", "&lt;")
                    .replace(">", "&gt;")
                    .replace("\"", "&quot;")
                    .replace("'", "&#x27;")
                    .replace("/", "&#x2F;");
    }
}


To run this code, you need to have a servlet container like Apache Tomcat. You also need to configure your web.xml file or use annotations for servlet mapping if required by the servlet version being used. Here is an example of how you might map the servlet in `web.xml`:


<web-app xmlns="http://xmlns.jcp.org/xml/ns/javaee"
         xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
         xsi:schemaLocation="http://xmlns.jcp.org/xml/ns/javaee http://xmlns.jcp.org/xml/ns/javaee/web-app_4_0.xsd"
         version="4.0">

    <servlet>
        <servlet-name>HelloServlet</servlet-name>
        <servlet-class>HelloServlet</servlet-class>
    </servlet>

    <servlet-mapping>
        <servlet-name>HelloServlet</servlet-name>
        <url-pattern>/hello/*</url-pattern>
    </servlet-mapping>

</web-app>