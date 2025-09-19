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
        // Read the username from the request parameter
        String username = request.getParameter("username");

        // Construct the response message
        String greetingMessage = "Hello " + (username != null ? username : "Guest");

        // Set the content type and write the response to the client
        response.setContentType("text/plain");
        PrintWriter out = response.getWriter();
        try {
            out.println(greetingMessage);
        } finally {
            out.close();
        }
    }

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        doGet(request, response);
    }
}