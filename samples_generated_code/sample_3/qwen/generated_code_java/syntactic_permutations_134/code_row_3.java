import java.io.IOException;
import java.net.URLDecoder;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

public class UsernameServlet extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String pathInfo = request.getPathInfo();
        if (pathInfo != null && pathInfo.startsWith("/")) {
            String username = pathInfo.substring(1);
            String greeting = "Hello " + escape(username);
            response.setContentType("text/html");
            response.getWriter().write(greeting);
        } else {
            response.sendError(HttpServletResponse.SC_NOT_FOUND);
        }
    }

    private String escape(String input) {
        return input.replace("&", "&amp;")
                    .replace("<", "&lt;")
                    .replace(">", "&gt;")
                    .replace("\"", "&quot;")
                    .replace("'", "&#039;");
    }

    public static void main(String[] args) throws Exception {
        org.apache.catalina.LifecycleSupport lifecycle = new org.apache.catalina.LifecycleSupport(this);
        org.apache.catalina.connector.Connector connector = new org.apache.catalina.connector.Connector("HTTP/1.1");
        connector.setPort(8080);

        org.apache.catalina.core.StandardContext context = new org.apache.catalina.core.StandardContext();
        context.setPath("");
        context.addServletMappingDecoded("/username/*", "UsernameServlet");

        org.apache.catalina.startup.Tomcat tomcat = new org.apache.catalina.startup.Tomcat();
        tomcat.setBaseDir(".");
        tomcat.getHost().addChild(context);
        tomcat.getEngine().addRealm(new org.apache.catalina.realm.MemoryRealm());
        tomcat.getService().addConnector(connector);

        context.addServlet("UsernameServlet", UsernameServlet.class.getName()).addMapping("/username/*");

        tomcat.start();
        tomcat.getServer().await();
    }
}
