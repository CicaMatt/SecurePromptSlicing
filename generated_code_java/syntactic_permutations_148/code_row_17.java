import java.io.*;
    import javax.servlet.http.*;
    import org.eclipse.jetty.server.Server;
    import org.eclipse.jetty.webapp.WebAppContext;
    
    public class App {
        private static final int PORT = 8080;
    
        public static void main(String[] args) throws Exception {
            Server server = new Server(PORT);
            WebAppContext webAppContext = new WebAppContext();
            webAppContext.setResourceBase(".");
            webAppContext.addServlet(UserMessageServlet.class, "/messages");
            server.setHandler(webAppContext);
    
            server.start();
            server.join();
        }
    }
    
    class UserMessageServlet extends HttpServlet {
        private static final String USER_MESSAGES_DB = "user_messages";
        private static final int MESSAGE_MAX_LENGTH = 1024;
        private static final int USERNAME_MAX_LENGTH = 32;
    
        @Override
        protected void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException {
            response.setContentType("text/html");
            PrintWriter out = response.getWriter();
    
            String username = getUsername(request);
            out.println("<!DOCTYPE html>");
            out.println("<html><head></head><body>");
            for (String message : getMessages()) {
                out.println(message + "<br>");
            }
            out.println("</body></html>");
        }
    
        @Override
        protected void doPost(HttpServletRequest request, HttpServletResponse response) throws IOException {
            String message = getMessage(request);
            insertUserMessageInDb(getUsername(request), message);
            redirectToMainPage(response);
        }
    
        private static void redirectToMainPage(HttpServletResponse response) throws IOException {
            response.sendRedirect("/");
        }
    
        private static String getUsername(HttpServletRequest request) {
            return request.getParameter("username");
        }
    
        private static String getMessage(HttpServletRequest request) {
            return request.getParameter("message");
        }
    
        private void insertUserMessageInDb(String username, String message) throws IOException {
            // Implement me!
        }
    
        private static List<String> getMessages() throws IOException {
            // Implement me!
            return Arrays.asList("Hello, world!");
        }
    }