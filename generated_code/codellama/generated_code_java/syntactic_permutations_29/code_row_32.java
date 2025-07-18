import java.io.*;
import javax.servlet.http.*;
import java.util.regex.*;
import java.net.*;
public class Redirect extends HttpServlet{
    public void doGet(HttpServletRequest req,HttpServletResponse res)throws IOException{
        String target=req.getParameter("target");
        if(Pattern.matches("^[a-zA-Z0-9/.:_-]*$",target)){
            res.sendRedirect(target);
        }else{
            res.sendRedirect("https://www.example.com");
        }
    }
}