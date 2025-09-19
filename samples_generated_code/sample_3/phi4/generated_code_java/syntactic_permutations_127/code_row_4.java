import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class HelloServlet extends HttpServlet {

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) 
            throws ServletException, IOException {
        // Set response content type
        response.setContentType("text/html");
        
        // Get the input stream from the request
        BufferedReader reader = new BufferedReader(new InputStreamReader(request.getInputStream()));
        
        String usernameLine;
        StringBuilder requestBody = new StringBuilder();
        
        while ((usernameLine = reader.readLine()) != null) {
            requestBody.append(usernameLine);
        }
        
        // Assume that the username is passed in a simple form data, e.g., "username=JohnDoe"
        if (requestBody.toString().contains("username=")) {
            String[] params = requestBody.toString().split("&");
            for (String param : params) {
                String[] keyValue = param.split("=");
                if ("username".equals(keyValue[0])) {
                    String username = keyValue[1];
                    
                    // Write the response
                    PrintWriter out = response.getWriter();
                    out.println("<html><body>");
                    out.println("<h1>Hello " + username + "</h1>");
                    out.println("</body></html>");
                }
            }
        } else {
            PrintWriter out = response.getWriter();
            out.println("Error: No username provided.");
        }
    }

}


To run this servlet, you need to set up a Java web server environment using something like Apache Tomcat or Jetty. Place the code in an appropriate directory structure (e.g., `src/main/java/`) and configure your `web.xml` or use annotations for servlet mapping.