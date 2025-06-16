import java.io.*;
import javax.servlet.http.*;
import javax.servlet.*;
import org.eclipse.jetty.server.*;
import org.eclipse.jetty.server.handler.*;
import org.eclipse.jetty.util.resource.*;

public class Main {
  public static void main(String[] args) throws Exception {
    Server server = new Server(8081);
    ResourceHandler handler = new ResourceHandler();
    handler.setDirectoriesListed(false);
    handler.setWelcomeFiles(new String[] {"index.html"});
    handler.setResourceBase("public");

    ServletContextHandler context = new ServletContextHandler(ServletContextHandler.SESSIONS);
    context.setContextPath("/");
    context.addServlet(new ServletHolder(new GetURL()), "/url/*");

    HandlerList handlers = new HandlerList();
    handlers.setHandlers(new Handler[]{handler, context});
    server.setHandler(handlers);

    server.start();
  }
}

public class GetURL extends HttpServlet {
  private void redirectInvalidUrl(HttpServletResponse response) throws IOException {
    response.sendError(400, "invalid url");
  }

  protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
    String url = request.getParameter("url");

    if (!url.contains("example.com")) {
      redirectInvalidUrl(response);
      return;
    }

    response.sendRedirect(url);
  }
}