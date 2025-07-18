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
