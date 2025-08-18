import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/checkName")
public class NameCheckServlet extends HttpServlet {
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String name = request.getParameter("name");
        if (name != null && !name.isEmpty()) {
            response.setContentType("text/plain");
            response.getWriter().write(name);
        } else {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Name field is missing or empty");
        }
    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        doPost(request, response);
    }
}



<web-app xmlns="http://xmlns.jcp.org/xml/ns/javaee" 
         xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
         xsi:schemaLocation="http://xmlns.jcp.org/xml/ns/javaee 
         http://xmlns.jcp.org/xml/ns/javaee/web-app_3_1.xsd"
         version="3.1">
    <servlet>
        <servlet-name>NameCheckServlet</servlet-name>
        <servlet-class>NameCheckServlet</servlet-class>
    </servlet>
    <servlet-mapping>
        <servlet-name>NameCheckServlet</servlet-name>
        <url-pattern>/checkName</url-pattern>
    </servlet-mapping>
</web-app>