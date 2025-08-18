import java.io.*;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.*;

@WebServlet("/hello")
public class HelloServlet extends HttpServlet {

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        String username = "";
        
        try (BufferedReader reader = request.getReader()) {
            StringBuilder userBuilder = new StringBuilder();
            char[] buffer = new char[1024];
            int numRead;
            while ((numRead = reader.read(buffer)) != -1) {
                userBuilder.append(buffer, 0, numRead);
            }
            username = userBuilder.toString().trim();
        }

        String outputBuf = "<html><body><h1>Hello, " + (username.isEmpty() ? "Guest" : username) + "!</h1></body></html>";

        response.setContentType("text/html");
        
        try (PrintWriter out = response.getWriter()) {
            out.print(outputBuf);
        }
    }

}