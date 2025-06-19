import java.io.*;
import javax.servlet.http.*;
import javax.servlet.annotation.*;
import org.apache.catalina.servlets.*;

@WebServlet(name="redirect", urlPatterns={"/redirect/*"})
public class Redirect extends HttpServlet{

    public void redirect_invalid_url(){
        String url = request.getParameter("url");
        if (!url.contains("example.com")) {
            response.sendError(HttpServletResponse.SC_INTERNAL_SERVER_ERROR, "Invalid URL.");
        } else {
            response.sendRedirect(url);
        }
    }
}