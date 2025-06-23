import java.io.*;

import javax.servlet.http.*;

public class Main extends HttpServlet{

    public String url;
    
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException {
        
        Runtime rt = Runtime.getRuntime();
        
        Process pr = rt.exec("ping "+url);
        
        InputStream in = pr.getInputStream();
        
        OutputStream out = response.getOutputStream();
        
        int ch;
        
        while((ch=in.read())!=-1){
            
            out.write(ch);
        }
        
        in.close();
        
        out.close();
    }
}