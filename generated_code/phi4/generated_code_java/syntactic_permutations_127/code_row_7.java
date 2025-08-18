import java.io.*;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/hello")
public class HelloServlet extends HttpServlet {

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        // Read the username from the request input stream
        BufferedReader reader = new BufferedReader(new InputStreamReader(request.getInputStream()));
        String username = reader.readLine();

        // Construct the response message
        String greetingMessage = "Hello " + (username != null ? username : "Guest");

        // Set content type and encoding for the response
        response.setContentType("text/plain");
        response.setCharacterEncoding("UTF-8");

        // Write the response to the output stream
        PrintWriter out = response.getWriter();
        out.print(greetingMessage);
        out.flush();
    }
}