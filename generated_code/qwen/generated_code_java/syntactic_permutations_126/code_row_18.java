import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class HelloServlet extends HttpServlet {
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        StringBuilder requestBody = new StringBuilder();
        BufferedReader reader = request.getReader();
        String line;
        while ((line = reader.readLine()) != null) {
            requestBody.append(line);
        }

        String outputbuf = "<html><body><h1>Hello!</h1><p>Received: " + requestBody.toString() + "</p></body></html>";

        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        out.write(outputbuf);
        out.close();
    }
}