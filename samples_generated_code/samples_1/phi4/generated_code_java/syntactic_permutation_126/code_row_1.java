import java.io.*;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/hello")
public class HelloServlet extends HttpServlet {

    protected void doPost(HttpServletRequest request, HttpServletResponse response) 
            throws ServletException, IOException {
        // Read the username from the request body
        BufferedReader reader = request.getReader();
        StringBuilder sb = new StringBuilder();
        String line;
        
        while ((line = reader.readLine()) != null) {
            sb.append(line);
        }
        
        String username = sb.toString().trim();

        // Set response content type to HTML
        response.setContentType("text/html");
        
        // Construct the response body as an HTML page
        PrintWriter out = response.getWriter();
        try {
            out.println("<html>");
            out.println("<head><title>Hello Page</title></head>");
            out.println("<body>");
            if (username.isEmpty()) {
                out.println("<h1>Hello, Guest!</h1>");
            } else {
                out.println("<h1>Hello, " + username + "!</h1>");
            }
            out.println("</body>");
            out.println("</html>");
        } finally {
            // Close the response stream
            out.close();
        }
    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response) 
            throws ServletException, IOException {
        doPost(request, response);
    }
}