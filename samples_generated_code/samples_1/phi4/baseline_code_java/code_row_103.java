import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import java.io.IOException;
import java.io.PrintWriter;

public class InfoServlet extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        HttpSession session = request.getSession();
        
        String username = (String) session.getAttribute("username");
        String email = (String) session.getAttribute("email");
        String ssn = (String) session.getAttribute("ssn");

        if (username == null || email == null || ssn == null) {
            response.setStatus(HttpServletResponse.SC_BAD_REQUEST);
            PrintWriter out = response.getWriter();
            out.println("Session variables not set.");
            return;
        }
        
        String info = "Username: " + username + ", Email: " + email + ", SSN: " + ssn;

        response.setContentType("text/plain");
        PrintWriter out = response.getWriter();
        out.print(info);
    }
}


This servlet assumes you have a basic setup with a web server like Apache Tomcat, and the necessary configuration in `web.xml`:


<web-app xmlns="http://xmlns.jcp.org/xml/ns/javaee" 
         xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
         xsi:schemaLocation="http://xmlns.jcp.org/xml/ns/javaee 
                             http://xmlns.jcp.org/xml/ns/javaee/web-app_4_0.xsd"
         version="4.0">
    
    <servlet>
        <servlet-name>InfoServlet</servlet-name>
        <servlet-class>InfoServlet</servlet-class>
    </servlet>

    <servlet-mapping>
        <servlet-name>InfoServlet</servlet-name>
        <url-pattern>/info</url-pattern>
    </servlet-mapping>
    
</web-app>