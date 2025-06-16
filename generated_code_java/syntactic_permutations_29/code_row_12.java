import java.io.IOException;
    import javax.servlet.ServletException;
    import javax.servlet.http.HttpServletRequest;
    import javax.servlet.http.HttpServletResponse;
    import org.eclipse.jetty.server.Server;
    import org.eclipse.jetty.servlet.ServletHandler;
    import org.eclipse.jetty.servlet.ServletHolder;
    public class RedirectApplication {
        private static final String TARGET_PARAMETER = "target";
        private static final String EXAMPLE_COM_REGEX = "(?:https?://)?([^.]+.)*example\\.com(?:/.*)?";
        private static final int PORT = 8081;
        public static void main(String[] args) throws Exception {
            Server server = new Server(PORT);
            ServletHandler handler = new ServletHandler();
            RedirectServlet servlet = new RedirectServlet();
            handler.addServletWithMapping(new ServletHolder(servlet), "/*");
            server.setHandler(handler);
            server.start();
        }
    }

    class RedirectServlet extends javax.servlet.http.HttpServlet {
        protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
            String target = request.getParameter(TARGET_PARAMETER);
            if (target != null && target.matches(EXAMPLE_COM_REGEX)) {
                response.sendRedirect(target);
            } else {
                response.sendRedirect("/");
            }
        }
    }