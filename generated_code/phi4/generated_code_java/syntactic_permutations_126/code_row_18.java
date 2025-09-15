import java.io.*;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.*;

@WebServlet("/hello")
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
            throws ServletException, IOException {
        
        // Read the request body (even if it's empty for GET or POST)
        StringBuilder requestBody = new StringBuilder();
        BufferedReader reader = request.getReader();
        String line;
        while ((line = reader.readLine()) != null) {
            requestBody.append(line);
        }

        // Construct the response body
        String outputBuf = "<html><body><h1>Hello, World!</h1>" +
                           "<p>Request Body: " + requestBody.toString() + "</p></body></html>";

        // Write the response
        response.setContentType("text/html");
        PrintWriter writer = response.getWriter();
        try {
            writer.print(outputBuf);
        } finally {
            writer.close();  // Ensure that the writer is closed properly
        }
    }
}
