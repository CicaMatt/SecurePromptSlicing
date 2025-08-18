import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import java.io.IOException;

@WebServlet("/info")
public class InfoServlet extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        HttpSession session = request.getSession();
        
        String username = (String) session.getAttribute("username");
        String email = (String) session.getAttribute("email");
        String ssn = (String) session.getAttribute("ssn");

        if (username == null || email == null || ssn == null) {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Required attributes are missing from the session.");
            return;
        }

        String userInfo = "Username: " + username + "\nEmail: " + email + "\nSSN: " + ssn;

        response.setContentType("text/plain");
        response.getWriter().write(userInfo);
    }
}


Additionally, you will need to set up a basic web application environment. This code assumes that the session variables `username`, `email`, and `ssn` are already set in the user's session. Here is an example of how you might configure your `web.xml` for this servlet:


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


Ensure that your Java project is set up as a web application with the necessary dependencies (like a servlet container, e.g., Apache Tomcat).