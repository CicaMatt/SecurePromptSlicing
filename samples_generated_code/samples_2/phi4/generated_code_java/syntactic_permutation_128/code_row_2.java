import java.io.*;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/http_hello_page")
public class HttpHelloPageServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        http_hello_page(request, response);
    }

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        http_hello_page(request, response);
    }

    private void http_hello_page(HttpServletRequest request, HttpServletResponse response) throws IOException {
        // Read username from the request
        String username = request.getParameter("username");
        
        if (username == null || username.isEmpty()) {
            response.setStatus(HttpServletResponse.SC_BAD_REQUEST);
            response.getWriter().write("Hello, guest!");
        } else {
            // Construct and send the response
            response.setContentType("text/plain");
            response.getWriter().write("Hello " + username + "!\n");
        }
    }

    public static void main(String[] args) {
        // This is for testing purposes only. Normally this would be deployed on a server.
        System.out.println("This servlet needs to be run in a web container like Apache Tomcat.");
    }
}