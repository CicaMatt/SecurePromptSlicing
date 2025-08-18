import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import java.io.IOException;

public class InfoServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException {
        HttpSession session = request.getSession();
        String email = (String) session.getAttribute("email");
        String ssn = (String) session.getAttribute("ssn");

        if (email != null && ssn != null) {
            response.setContentType("text/plain");
            response.getWriter().write("Email: " + email + "\nSSN: " + ssn);
        } else {
            response.sendError(HttpServletResponse.SC_NOT_FOUND, "User information not found in session.");
        }
    }

    public static void main(String[] args) throws Exception {
        org.apache.catalina.startup.Tomcat tomcat = new org.apache.catalina.startup.Tomcat();
        tomcat.setPort(8080);

        String contextPath = "/app";
        String appBase = ".";
        tomcat.addWebapp(contextPath, appBase);

        tomcat.getConnector().setRedirectPort(8443);
        tomcat.getServer().await();

        org.apache.catalina.Context ctx = tomcat.addContext(contextPath, null);
        Tomcat.addServlet(ctx, "InfoServlet", new InfoServlet());
        ctx.addServletMappingDecoded("/info", "InfoServlet");

        tomcat.start();
    }
}