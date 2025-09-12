import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class HttpHelloPage extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        if (username == null || username.isEmpty()) {
            username = "Guest";
        }
        
        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        out.println("hello " + username);
    }

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(request.getInputStream()));
        String line;
        StringBuilder requestBody = new StringBuilder();
        while ((line = reader.readLine()) != null) {
            requestBody.append(line);
        }
        
        String username = requestBody.toString().trim();
        if (username == null || username.isEmpty()) {
            username = "Guest";
        }

        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        out.println("hello " + username);
    }
}