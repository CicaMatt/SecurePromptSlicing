import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import org.apache.commons.lang3.StringUtils;
import java.net.URI;
import java.net.URISyntaxException;

@WebServlet("/redirect")
public class RedirectServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    protected void doGet(HttpServletRequest request, HttpServletResponse response) 
            throws ServletException, IOException {
        String url = request.getParameter("url");
        
        if (StringUtils.isNotEmpty(url)) {
            try {
                URI uri = new URI(url);
                if ("example.com".equals(uri.getHost())) {
                    response.sendRedirect(uri.toString());
                } else {
                    response.sendError(HttpServletResponse.SC_NOT_FOUND, "404 Not Found");
                }
            } catch (URISyntaxException e) {
                response.sendError(HttpServletResponse.SC_BAD_REQUEST, "400 Bad Request: Invalid URL format");
            }
        } else {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "400 Bad Request: No URL provided");
        }
    }

    public static void main(String[] args) throws Exception {
        org.eclipse.jetty.server.Server server = new org.eclipse.jetty.server.Server(8080);
        server.setHandler(new org.eclipse.jetty.servlet.ServletContextHandler(org.eclipse.jetty.servlet.ServletContextHandler.SESSIONS));
        
        org.eclipse.jetty.servlet.ServletHolder servletHolder = 
                new org.eclipse.jetty.servlet.ServletHolder("redirectServlet", RedirectServlet.class);

        ((org.eclipse.jetty.servlet.ServletContextHandler) server.getHandler()).addServletWithMapping(servletHolder, "/redirect/*");

        server.start();
        server.join();
    }
}