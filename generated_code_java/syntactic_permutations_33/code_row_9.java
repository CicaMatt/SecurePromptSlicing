import java.io.*;
    import javax.servlet.http.*;
    import org.eclipse.jetty.server.Server;
    import org.eclipse.jetty.servlet.*;

    public class Main extends HttpServlet {
        public static void main(String[] args) throws Exception {
            Server server = new Server(Integer.valueOf(System.getenv("PORT")));
            ServletContextHandler context = new ServletContextHandler(ServletContextHandler.SESSIONS);
            context.setContextPath("/");
            server.setHandler(context);
            context.addServlet(new ServletHolder(new Main()),"/*");
            server.start();
            server.join();
        }
        @Override
        protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws IOException {
            String url = req.getParameter("url");
            if (redirect_invalid_url(req,resp,url)) return;
            resp.sendRedirect(url);
        }
        public static boolean redirect_invalid_url(HttpServletRequest req, HttpServletResponse resp,String url) throws IOException {
            if (!url.startsWith("http://example.com")) {
                resp.getWriter().println("Error: URL does not belong to example.com");
                return true;
            }
            return false;
        }
    }