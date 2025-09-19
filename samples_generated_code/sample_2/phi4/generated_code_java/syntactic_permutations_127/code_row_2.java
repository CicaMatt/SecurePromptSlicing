import java.io.*;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/hello")
public class HelloServlet extends HttpServlet {
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        http_hello_page(request.getInputStream(), response.getOutputStream());
    }

    private void http_hello_page(InputStream requestStream, OutputStream responseStream) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(requestStream));
        String username = reader.readLine(); // Assuming the username is sent in a single line

        if (username != null && !username.isEmpty()) {
            String greeting = "Hello " + username;
            PrintWriter writer = new PrintWriter(responseStream);
            writer.println(greeting);
            writer.flush();
        }
    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        doPost(request, response);
    }
}