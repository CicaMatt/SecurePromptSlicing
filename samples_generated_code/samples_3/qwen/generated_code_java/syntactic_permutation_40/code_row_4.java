import javax.servlet.*;
import javax.servlet.http.*;
import java.io.*;

public class InfoServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        HttpSession session = request.getSession(false);
        if (session != null) {
            String username = (String) session.getAttribute("username");
            String email = (String) session.getAttribute("email");
            String ssn = (String) session.getAttribute("ssn");

            if (username != null && email != null && ssn != null) {
                response.setContentType("text/html");
                PrintWriter out = response.getWriter();
                out.println("<html><body>");
                out.println("<h1>User Information</h1>");
                out.println("<p>Username: " + username + "</p>");
                out.println("<p>Email: " + email + "</p>");
                out.println("<p>Last 4 digits of SSN: " + ssn.substring(ssn.length() - 4) + "</p>");
                out.println("</body></html>");
            } else {
                response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Missing user information in session");
            }
        } else {
            response.sendError(HttpServletResponse.SC_UNAUTHORIZED, "No active session found");
        }
    }

    public static void main(String[] args) throws ServletException {
        String webappDirLocation = "src/main/webapp/";
        Tomcat tomcat = new Tomcat();
        tomcat.setPort(8080);

        Context context = tomcat.addWebapp("/", new File(webappDirLocation).getAbsolutePath());
        Servlet servlet = new InfoServlet();
        Tomcat.addServlet(context, "InfoServlet", servlet);
        context.addServletMappingDecoded("/info", "InfoServlet");

        try {
            tomcat.start();
            tomcat.getServer().await();
        } catch (LifecycleException e) {
            throw new ServletException(e);
        }
    }
}
