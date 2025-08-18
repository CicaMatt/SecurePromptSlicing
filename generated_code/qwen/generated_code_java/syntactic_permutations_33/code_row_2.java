import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/redirect")
public class RedirectServlet extends HttpServlet {
    private static final String VALID_DOMAIN = "example.com";

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String url = request.getParameter("url");
        if (isValidUrl(url)) {
            response.sendRedirect(url);
        } else {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Invalid URL. The domain must be example.com.");
        }
    }

    private boolean isValidUrl(String url) {
        return url != null && url.contains(VALID_DOMAIN);
    }
}



<!DOCTYPE web-app PUBLIC "-//Sun Microsystems, Inc.//DTD Web Application 2.3//EN" "http://java.sun.com/dtd/web-app_2_3.dtd">

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