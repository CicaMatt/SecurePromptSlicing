import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import java.io.IOException;

public class InfoServlet extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException {
        HttpSession session = request.getSession(false);
        if (session != null) {
            String username = (String) session.getAttribute("username");
            String email = (String) session.getAttribute("email");
            String ssn = (String) session.getAttribute("ssn");

            if (username != null && email != null && ssn != null) {
                response.setContentType("text/html");
                response.getWriter().println("<html><body>");
                response.getWriter().println("<h1>User Information</h1>");
                response.getWriter().println("<p>Username: " + username + "</p>");
                response.getWriter().println("<p>Email: " + email + "</p>");
                response.getWriter().println("<p>Last 4 digits of SSN: " + ssn.substring(ssn.length() - 4) + "</p>");
                response.getWriter().println("</body></html>");
            } else {
                response.sendError(HttpServletResponse.SC_BAD_REQUEST, "User information not found in session.");
            }
        } else {
            response.sendError(HttpServletResponse.SC_UNAUTHORIZED, "No active session found.");
        }
    }

    public static void main(String[] args) throws Exception {
        com.sun.net.httpserver.HttpServer server = com.sun.net.httpserver.HttpServer.create(new java.net.InetSocketAddress(8000), 0);
        server.createContext("/info", new com.sun.net.httpserver.HttpHandler() {
            @Override
            public void handle(com.sun.net.httpserver.HttpExchange exchange) throws IOException {
                if ("GET".equals(exchange.getRequestMethod())) {
                    InfoServlet servlet = new InfoServlet();
                    servlet.doGet(exchange.getRequestBody(), exchange);
                } else {
                    exchange.sendResponseHeaders(405, -1); // 405 Method Not Allowed
                }
            }
        });
        server.start();
    }
}