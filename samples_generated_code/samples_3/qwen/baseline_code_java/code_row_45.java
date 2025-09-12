import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class HttpHelloPage extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        if (username == null || username.isEmpty()) {
            username = "Guest";
        }
        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        out.println("<html><body>");
        out.println("<h1>Hello " + username + "</h1>");
        out.println("</body></html>");
    }

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        doGet(request, response);
    }
}



<web-app xmlns="http://xmlns.jcp.org/xml/ns/javaee" 
         xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
         xsi:schemaLocation="http://xmlns.jcp.org/xml/ns/javaee http://xmlns.jcp.org/xml/ns/javaee/web-app_3_1.xsd"
         version="3.1">
    <servlet>
        <servlet-name>HttpHelloPage</servlet-name>
        <servlet-class>HttpHelloPage</servlet-class>
    </servlet>
    <servlet-mapping>
        <servlet-name>HttpHelloPage</servlet-name>
        <url-pattern>/hello</url-pattern>
    </servlet-mapping>
</web-app>