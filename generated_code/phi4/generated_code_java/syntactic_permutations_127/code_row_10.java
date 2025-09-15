import java.io.*;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/http_hello_page")
public class HttpHelloPageServlet extends HttpServlet {

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        handleRequest(request, response);
    }

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        handleRequest(request, response);
    }
    
    private void handleRequest(HttpServletRequest httpRequest, HttpServletResponse httpResponse) throws IOException {
        String username = httpRequest.getParameter("username");

        if (username != null && !username.trim().isEmpty()) {
            httpResponse.setContentType("text/plain");
            PrintWriter out = httpResponse.getWriter();
            out.println("Hello " + username);
        } else {
            httpResponse.sendError(HttpServletResponse.SC_BAD_REQUEST, "Username is required.");
        }
    }
}
