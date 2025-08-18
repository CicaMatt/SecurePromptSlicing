import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class HttpHelloServlet extends HttpServlet {

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        processRequest(request, response);
    }

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        processRequest(request, response);
    }

    private void processRequest(HttpServletRequest request, HttpServletResponse response) throws IOException {
        String username = request.getParameter("username");

        if (username == null || username.isEmpty()) {
            username = "Guest";
        }

        response.setContentType("text/plain");
        PrintWriter out = response.getWriter();
        try {
            out.print("hello " + username);
        } finally {
            out.close();
        }
    }

    public static void main(String[] args) throws Exception {
        // For testing purposes, create a mock servlet environment
        HttpServer server = HttpServer.create(new InetSocketAddress(8000), 0);
        HttpContext context = server.createContext("/hello", new HttpHelloServlet());
        server.setExecutor(null); // creates a default executor
        server.start();
        
        System.out.println("Server is listening on port 8000. Press Ctrl+C to stop.");
    }
}