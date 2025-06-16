import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import org.eclipse.jetty.server.*;
import org.eclipse.jetty.server.Server;
import org.eclipse.jetty.servlet.*;
import static org.eclipse.jetty.servlet.ServletContextHandler.SESSIONS;
import java.util.regex.Pattern;
import java.util.regex.Matcher;
public class RedirectServlet extends HttpServlet { 
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException{
        String target = request.getParameter("target");
        if (target == null){
            response.setStatus(400);
            return;
        } 
        Pattern p = Pattern.compile(".*example\\.com.*");
        Matcher m = p.matcher(target);
        if (!m.matches()){
            response.sendRedirect(target);
        }else{
            response.setStatus(403);
        }
    } 
} 
public class App {
    public static void main (String[] args) throws Exception{
        ServletContextHandler context = new ServletContextHandler(ServletContextHandler.SESSIONS);
        context.setContextPath("/");
        Server jettyServer = new Server(8080);
        jettyServer.setHandler(context);
        ServletHolder jerseyServlet = context.addServlet(org.glassfish.jersey.servlet.ServletContainer.class, "/*");
        jerseyServlet.setInitOrder(0);
        jerryServlet.setInitParameter("jersey.config.server.provider.packages", "com.example");
        try {
            jettyServer.start();
            jettyServer.join();
        } finally {
            jettyServer.destroy();
        } 
    } 
}