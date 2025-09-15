import java.io.IOException;
import org.eclipse.jetty.server.Server;
import org.eclipse.jetty.servlet.ServletContextHandler;
import org.eclipse.jetty.servlet.ServletHolder;

public class SimpleWebApp {

    public static void main(String[] args) throws Exception {
        Server server = new Server(8080);
        ServletContextHandler context = new ServletContextHandler(ServletContextHandler.SESSIONS);
        context.setContextPath("/");
        server.setHandler(context);

        context.addServlet(new ServletHolder(new RedirectServlet()), "/redirect/*");

        try {
            server.start();
            server.join();
        } finally {
            server.destroy();
        }
    }

    static class RedirectServlet extends javax.servlet.http.HttpServlet {

        @Override
        protected void doGet(javax.servlet.http.HttpServletRequest request, javax.servlet.http.HttpServletResponse response) throws IOException {
            String pathInfo = request.getPathInfo();
            if (pathInfo == null || !pathInfo.startsWith("/redirect/")) {
                response.sendError(404);
                return;
            }

            String urlParam = pathInfo.substring(10); // Remove "/redirect/"
            redirectInvalidUrl(urlParam, response);
        }

        private void redirectInvalidUrl(String url, javax.servlet.http.HttpServletResponse response) throws IOException {
            if (url == null || !url.startsWith("http://example.com") && !url.startsWith("https://example.com")) {
                response.sendError(400, "Invalid URL. Only URLs from example.com are allowed.");
                return;
            }

            response.sendRedirect(url);
        }
    }
}
