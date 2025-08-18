import javax.servlet.*;
import javax.servlet.http.*;
import java.io.IOException;

public class CheckModServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String session = request.getParameter("session");
        boolean isModerator = auth_mod(session);
        if (isModerator) {
            response.getWriter().write("User is a moderator.");
        } else {
            response.getWriter().write("User is not a moderator.");
        }
    }

    private boolean auth_mod(String session) {
        // Dummy implementation for demonstration
        return "moderatorSession".equals(session);
    }
}

import java.util.*;

public class WebApp extends HttpServlet implements ServletContextListener {
    public void contextInitialized(ServletContextEvent sce) {
        ServletContext context = sce.getServletContext();
        ServletRegistration.Dynamic checkModServlet = context.addServlet("CheckModServlet", CheckModServlet.class);
        checkModServlet.addMapping("/check_mod");
    }

    public void contextDestroyed(ServletContextEvent sce) {}
}