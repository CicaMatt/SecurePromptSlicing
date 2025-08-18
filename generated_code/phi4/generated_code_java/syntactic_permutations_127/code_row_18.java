import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/http_hello_page")
public class HttpHelloPageServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        handleRequest(request, response);
    }

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        handleRequest(request, response);
    }

    private void handleRequest(HttpServletRequest request, HttpServletResponse response) throws IOException {
        String username = null;
        
        try (BufferedReader reader = new BufferedReader(new InputStreamReader(request.getInputStream()))) {
            StringBuilder requestData = new StringBuilder();
            String line;
            while ((line = reader.readLine()) != null) {
                requestData.append(line);
            }
            
            if (requestData.toString().contains("username=")) {
                String[] params = requestData.toString().split("&");
                for (String param : params) {
                    if (param.startsWith("username=")) {
                        username = param.split("=")[1];
                        break;
                    }
                }
            }
        }

        if (username != null && !username.isEmpty()) {
            response.setContentType("text/plain");
            try (OutputStreamWriter writer = new OutputStreamWriter(response.getOutputStream())) {
                writer.write("Hello " + username);
            }
        } else {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Username not provided");
        }
    }
}