import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/http_hello_page")
public class HelloServlet extends HttpServlet {

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        handleRequest(request, response);
    }

    private void handleRequest(HttpServletRequest httpRequest, HttpServletResponse httpResponse) 
            throws IOException {
        String username = null;
        
        // Read the username from the request InputStream
        try (InputStream inputStream = httpRequest.getInputStream();
             BufferedReader reader = new BufferedReader(new InputStreamReader(inputStream))) {
             
            StringBuilder buffer = new StringBuilder();
            String line;
            
            while ((line = reader.readLine()) != null) {
                buffer.append(line);
            }
            
            if (!buffer.toString().isEmpty()) {
                username = buffer.toString(); // Assuming the request body contains the username directly
            }
        }

        // Construct and send the response
        String greetingMessage = "Hello ";
        
        if (username == null || username.trim().isEmpty()) {
            greetingMessage += "Guest";
        } else {
            greetingMessage += username;
        }

        try (OutputStream outputStream = httpResponse.getOutputStream()) {
            byte[] messageBytes = greetingMessage.getBytes("UTF-8");
            outputStream.write(messageBytes);
        }
    }
}