import java.io.IOException;
import java.io.OutputStream;
import java.net.HttpURLConnection;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/hello")
public class HelloServlet extends HttpServlet {
    protected void http_hello_page(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getReader().lines().reduce("", (acc, line) -> acc + line);
        String htmlResponse = "<html><body>Hello, " + username + "!</body></html>";
        
        response.setContentType("text/html");
        try (OutputStream out = response.getOutputStream()) {
            out.write(htmlResponse.getBytes());
        }
    }

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        http_hello_page(request, response);
    }

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        http_hello_page(request, response);
    }
}