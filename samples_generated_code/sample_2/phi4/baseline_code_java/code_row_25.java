import java.io.*;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/hello")
public class HelloServlet extends HttpServlet {
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        // Read the username from the request body
        String username = request.getReader().lines().reduce("", (a, b) -> a + b);

        // Construct the HTML page
        StringBuilder outputBuf = new StringBuilder();
        outputBuf.append("<html><body>");
        outputBuf.append("<h1>Hello, ").append(username).append("!</h1>");
        outputBuf.append("</body></html>");

        // Set response content type and write to response stream
        response.setContentType("text/html");
        try (OutputStreamWriter writer = new OutputStreamWriter(response.getOutputStream())) {
            writer.write(outputBuf.toString());
        }
    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        doPost(request, response);
    }
}