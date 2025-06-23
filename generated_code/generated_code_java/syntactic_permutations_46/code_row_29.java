import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
public class Img extends HttpServlet {
    public void doGet(HttpServletRequest request,HttpServletResponse response)throws IOException,ServletException{
        String name=request.getParameter("name");
        File file=new File("/images/"+name);
        InputStream in=new FileInputStream(file);
        OutputStream out=response.getOutputStream();
        int c;
        while((c=in.read())!=-1){
            out.write((byte)c);
        }
        in.close();
        out.flush();
    }
}

### Explanation:
The decorator is written above the img() function associating the URL of /img with this function. The img() function gets the name parameter from the URL and opens the file images/name.The open() function returns a file object which is sent back to the browser as response output stream.