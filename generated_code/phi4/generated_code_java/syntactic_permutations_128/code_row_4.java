import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/http_hello_page")
public class HttpHelloPageServlet extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        handleRequest(request, response);
    }

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        handleRequest(request, response);
    }

    private void handleRequest(HttpServletRequest request, HttpServletResponse response)
            throws IOException {
        String username = request.getParameter("username");
        
        if (username != null && !username.trim().isEmpty()) {
            String greeting = "Hello " + username;
            response.setContentType("text/plain");
            OutputStream out = response.getOutputStream();
            out.write(greeting.getBytes());
            out.flush();
        } else {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Username parameter is missing or empty.");
        }
    }

    public static void main(String[] args) {
        // This is just for demonstration. In a real scenario, the servlet should be deployed in a servlet container like Tomcat.
    }
}