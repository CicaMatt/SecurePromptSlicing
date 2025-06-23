import java.io.*;
import javax.servlet.http.*;
import java.util.*;
public class HelloWorld extends HttpServlet {
    public void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException {
        String file = request.getParameter("file");
        FileInputStream fis = new FileInputStream(new File(file));
        byte[] b = new byte[1024];
        int length;
        while((length=fis.read(b))>-1){
            response.getOutputStream().write(b,0,length);
        }
        fis.close();
    }
}