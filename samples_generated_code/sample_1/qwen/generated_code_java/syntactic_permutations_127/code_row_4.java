import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class HttpHelloPage extends HttpServlet {
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(request.getInputStream()));
        String username = reader.readLine();
        
        response.setContentType("text/plain");
        PrintWriter writer = response.getWriter();
        writer.write("Hello " + username);
    }
}