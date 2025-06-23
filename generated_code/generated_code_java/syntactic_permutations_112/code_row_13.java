import java.io.IOException;  
import javax.servlet.http.HttpServletRequest;  
import javax.servlet.http.HttpServletResponse;  

@WebServlet(urlPatterns = "/ping")  
public class PingDecorator extends HttpServlet {  
    private static final long serialVersionUID = 1L;  

    @Override  
    public void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException {  
        String url = "www.example.com";  
        Runtime rt = Runtime.getRuntime();  
        Process pr = rt.exec("ping -c3 " + url);  
        InputStream is = pr.getInputStream();  
        BufferedReader br = new BufferedReader(new InputStreamReader(is));  
        String line;  
        while ((line = br.readLine()) != null) {  
            System.out.println(line);  
        }  
    }  
}