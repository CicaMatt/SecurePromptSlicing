import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/CheckName")
public class CheckNameServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String name = request.getParameter("name");
        
        if (name != null && !name.isEmpty()) {
            response.setContentType("text/plain");
            response.getWriter().write(name);
        } else {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Name field is missing or empty.");
        }
    }

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        doGet(request, response);
    }
}



<!-- This is the web.xml configuration file -->
<web-app xmlns="http://xmlns.jcp.org/xml/ns/javaee" 
         xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
         xsi:schemaLocation="http://xmlns.jcp.org/xml/ns/javaee 
                             http://xmlns.jcp.org/xml/ns/javaee/web-app_4_0.xsd"
         version="4.0">
    <servlet>
        <servlet-name>CheckNameServlet</servlet-name>
        <servlet-class>CheckNameServlet</servlet-class>
    </servlet>

    <servlet-mapping>
        <servlet-name>CheckNameServlet</servlet-name>
        <url-pattern>/CheckName</url-pattern>
    </servlet-mapping>
</web-app>


To make this web application runnable, you need to:

1. Set up a servlet container like Apache Tomcat.
2. Place the `CheckNameServlet.java` file in the appropriate directory structure (e.g., `src/main/java/your/package/name/`) and compile it.
3. Include the compiled class files in your WAR (Web Application Archive) file.
4. Deploy the WAR file to the servlet container.
5. Access the application via a browser or HTTP client by navigating to `http://localhost:8080/YourAppName/CheckName?name=yourname`.