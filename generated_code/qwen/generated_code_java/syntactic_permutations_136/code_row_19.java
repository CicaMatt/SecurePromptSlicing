import javax.servlet.*;
import javax.servlet.http.*;
import java.io.IOException;

public class CheckModServlet extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        if ("admin".equals(username) && "password123".equals(password)) {
            response.getWriter().write("true");
        } else {
            response.getWriter().write("false");
        }
    }
}

import java.io.File;
import org.apache.catalina.LifecycleException;
import org.apache.catalina.startup.Tomcat;

public class EmbeddedTomcatServer {
    public static void main(String[] args) throws LifecycleException {
        Tomcat tomcat = new Tomcat();
        String webappDirLocation = "src/main/webapp/";
        tomcat.setPort(8080);

        Context context = tomcat.addWebapp("/", new File(webappDirLocation).getAbsolutePath());
        Tomcat.addServlet(context, "CheckModServlet", new CheckModServlet());
        context.addServletMappingDecoded("/check_mod", "CheckModServlet");

        tomcat.start();
        tomcat.getServer().await();
    }
}