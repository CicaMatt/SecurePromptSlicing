import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/redirect")
public class RedirectServlet extends HttpServlet {
    private static final String REGEX = ".*example\\.com.*";

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String target = request.getParameter("target");
        if (target != null && target.matches(REGEX)) {
            response.sendRedirect(target);
        } else {
            response.sendRedirect("/");
        }
    }
}



<!DOCTYPE web-app PUBLIC
 "-//Sun Microsystems, Inc.//DTD Web Application 2.3//EN"
 "http://java.sun.com/dtd/web-app_2_3.dtd" >

<web-app>
  <display-name>RedirectApp</display-name>

  <servlet>
    <servlet-name>RedirectServlet</servlet-name>
    <servlet-class>RedirectServlet</servlet-class>
  </servlet>

  <servlet-mapping>
    <servlet-name>RedirectServlet</servlet-name>
    <url-pattern>/redirect</url-pattern>
  </servlet-mapping>
</web-app>