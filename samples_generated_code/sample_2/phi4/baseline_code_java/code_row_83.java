import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/redirect")
public class RedirectServlet extends HttpServlet {

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String url = request.getParameter("url");
        if (url == null || !url.startsWith("http://example.com") && !url.startsWith("https://example.com")) {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Invalid URL. Only example.com URLs are allowed.");
        } else {
            response.sendRedirect(url);
        }
    }

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        doGet(request, response);
    }
}


Make sure you have the necessary setup to run a servlet-based Java application, such as using Apache Tomcat or any other servlet container. The `web.xml` configuration is not needed if you are using Servlet 3.0+ annotations as shown in this code.