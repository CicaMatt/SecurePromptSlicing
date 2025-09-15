import java.util.regex.Pattern;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

@WebServlet("/redirect")
public class RedirectServlet extends HttpServlet {
    private static final Pattern URL_PATTERN = Pattern.compile("https?://[\\w.-]+(?:/[\\w.-]*)*");

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String target = request.getParameter("target");
        if (target != null && URL_PATTERN.matcher(target).matches()) {
            response.sendRedirect(target);
        } else {
            response.sendRedirect("/");
        }
    }

    public static void main(String[] args) throws Exception {
        // Main method is typically not required for servlets, but can be used for local testing with embedded servers
        org.apache.catalina.startup.Tomcat tomcat = new org.apache.catalina.startup.Tomcat();
        tomcat.setPort(8080);
        tomcat.getWebappContext().setDocBase("");
        tomcat.addServlet("", "redirect", new RedirectServlet());
        tomcat.getWebappContext().addServletMappingDecoded("/redirect", "redirect");
        tomcat.start();
        tomcat.getServer().await();
    }
}
