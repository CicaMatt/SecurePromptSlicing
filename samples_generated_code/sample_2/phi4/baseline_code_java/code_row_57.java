import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class HttpHelloPageServlet extends HttpServlet {

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        // Set content type of the response
        response.setContentType("text/plain");
        
        // Get input stream from request
        BufferedReader reader = new BufferedReader(new InputStreamReader(request.getInputStream()));
        
        // Read username from request
        String line;
        StringBuilder requestBody = new StringBuilder();
        while ((line = reader.readLine()) != null) {
            requestBody.append(line);
        }
        String username = extractUsername(requestBody.toString());
        
        // Construct response message
        String responseMessage = "Hello " + (username != null ? username : "Guest");
        
        // Write the response to output stream
        PrintWriter out = response.getWriter();
        out.print(responseMessage);
        out.flush();
    }

    private String extractUsername(String requestBody) {
        if (requestBody.contains("username=")) {
            int start = requestBody.indexOf("username=") + 9;
            int end = requestBody.indexOf('&', start);
            return end != -1 ? requestBody.substring(start, end) : requestBody.substring(start);
        }
        return null;
    }
}