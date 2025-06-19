import java.io.*;
import javax.servlet.http.*;

public class HelloWorldDecorator extends HttpServlet {
    public void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException{
        String url = "www.google.com";
        response.setContentType("text/plain");
        Runtime rt = Runtime.getRuntime();
        Process proc = rt.exec("ping " + url);
        
        // Read the output
        BufferedReader stdInput = new BufferedReader(new 
                InputStreamReader(proc.getInputStream()));
            
            // Read the output
            BufferedReader stdError = new BufferedReader(new 
                    InputStreamReader(proc.getErrorStream()));
            
            // Read the URL from the command line
            response.getWriter().println("URL: " + url);
            
            // Read the output into the buffer
            String s = null;
            while ((s = stdInput.readLine()) != null) {
                response.getWriter().println(s);
            }
    }
}