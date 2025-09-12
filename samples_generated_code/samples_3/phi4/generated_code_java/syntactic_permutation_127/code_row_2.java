import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.io.OutputStreamWriter;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/http_hello_page")
public class HttpHelloPageServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {

        String username = null;
        
        try (InputStream input = request.getInputStream();
             BufferedReader reader = new BufferedReader(new InputStreamReader(input));
             OutputStream output = response.getOutputStream();
             BufferedWriter writer = new BufferedWriter(new OutputStreamWriter(output))) {
            
            StringBuilder requestBody = new StringBuilder();
            String line;
            while ((line = reader.readLine()) != null) {
                requestBody.append(line);
            }
            
            if (requestBody.length() > 0) {
                username = parseUsername(requestBody.toString());
                
                if (username != null && !username.isEmpty()) {
                    writer.write("Hello " + username);
                } else {
                    writer.write("Hello Guest");
                }
            } else {
                writer.write("Hello Guest");
            }

            writer.flush();
        }
    }

    private String parseUsername(String requestBody) {
        try {
            int contentLength = Integer.parseInt(requestBody.substring(0, requestBody.indexOf("\r\n")).split(": ")[1]);
            String bodyContent = requestBody.substring(requestBody.indexOf("\r\n\r\n") + 4);
            
            if (bodyContent.length() >= contentLength) {
                return bodyContent.split("&")[0].split("=")[1];
            }
        } catch (Exception e) {
            // Handle exception
        }
        
        return null;
    }
}