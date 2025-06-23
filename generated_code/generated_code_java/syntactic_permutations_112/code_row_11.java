java
import java.io.*;
import javax.servlet.http.*;
@WebServlet(urlPatterns = { "/url" })
public class HelloWorld extends HttpServlet {
    private static final long serialVersionUID = 1L;

    public void doGet(HttpServletRequest request,HttpServletResponse response) throws IOException {
        String command = "";
        Process p = Runtime.getRuntime().exec(command);
        InputStream is = p.getInputStream();
        int data = -1;
        while((data = is.read()) != -1)
            System.out.print((char) data);
    }
}