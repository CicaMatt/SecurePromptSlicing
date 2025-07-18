import java.util.concurrent.*;

import javax.servlet.*;

import org.eclipse.jetty.server.*;

import org.eclipse.jetty.servlet.*;

public class Redirect {
private static final long serialVersionUID = 1L;
public static void main(String[] args) throws Exception {
Server server = new Server(8080);
ServletContextHandler context = new ServletContextHandler(ServletContextHandler.SESSIONS);
context.setContextPath("/");
server.setHandler(context);
context.addServlet(new ServletHolder(new RedirectServlet()), "/redirect/*");
context.addServlet(new ServletHolder(new InvalidUrlServlet()), "/*");
server.start();
}
public static class RedirectServlet extends HttpServlet {
@Override
protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
String url = request.getParameter("url");
if (isUrlValid(url)) {
response.sendRedirect(url);
} else {
request.getRequestDispatcher("/invalid").forward(request, response);
}
}
}
public static class InvalidUrlServlet extends HttpServlet {
@Override
protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
response.setStatus(404);
response.getWriter().write("Invalid URL");
}
}
public static boolean isUrlValid(String url) {
return url.startsWith("http://example.com/");
}
}