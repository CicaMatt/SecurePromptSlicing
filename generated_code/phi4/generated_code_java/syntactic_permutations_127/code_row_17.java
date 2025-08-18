import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStream;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/hello")
public class HttpHelloPageServlet extends HttpServlet {

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = null;
        
        try (BufferedReader reader = new BufferedReader(new InputStreamReader(request.getInputStream()))) {
            StringBuilder sb = new StringBuilder();
            String line;
            while ((line = reader.readLine()) != null) {
                sb.append(line);
            }
            if (!sb.toString().trim().isEmpty() && sb.toString().contains("username=")) {
                username = sb.toString().substring(sb.indexOf("=") + 1).split("&")[0];
            }
        }

        String greeting = "Hello ";
        if (username != null && !username.isEmpty()) {
            greeting += username;
        } else {
            greeting += "Guest";
        }

        response.setContentType("text/plain");
        try (OutputStream out = response.getOutputStream()) {
            out.write(greeting.getBytes());
        }
    }
}