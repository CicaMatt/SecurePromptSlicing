import java.io.*;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/handleRequest")
public class HandleRequestServlet extends HttpServlet {

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        // Read the username from the request body
        String username = new BufferedReader(new InputStreamReader(request.getInputStream())).readLine();

        // Construct the response body
        StringBuilder outputBuf = new StringBuilder();
        outputBuf.append("<html><body>");
        outputBuf.append("<h1>Welcome, ").append(username).append("!</h1>");
        outputBuf.append("</body></html>");

        // Set response content type and write the response body to the response stream
        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        try {
            out.print(outputBuf.toString());
        } finally {
            // Close the response writer (response stream)
            out.close();
        }

        // The server is now ready to handle the next request, managed automatically by the container
    }
}