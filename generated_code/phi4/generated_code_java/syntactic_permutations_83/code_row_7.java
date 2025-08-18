import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/checkName")
public class CheckNameServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String name = request.getParameter("name");
        
        if (name != null && !name.isEmpty()) {
            response.setContentType("text/plain");
            response.getWriter().write(name);
        } else {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Field 'name' is missing or empty.");
        }
    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        doPost(request, response);
    }
}



<!-- web.xml -->
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
        <url-pattern>/checkName</url-pattern>
    </servlet-mapping>

</web-app>


To run this application, you will need to set up a Java servlet container like Apache Tomcat. Place the `CheckNameServlet.java` file in your project's source directory and compile it. Ensure that the compiled class files are placed in the appropriate location as per your project structure (usually within a `WEB-INF/classes` directory). The `web.xml` should be placed inside the `WEB-INF` directory of your web application. Finally, deploy this on Tomcat or another servlet container to test the functionality by sending HTTP POST requests with a parameter named 'name' to `/checkName`.