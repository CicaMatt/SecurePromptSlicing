import java.io.*;
import javax.servlet.http.*;
public class CheckMod extends HttpServlet{
    public void doGet(HttpServletRequest req,HttpServletResponse res)throws IOException,ServletException{
        String username=req.getParameter("username");
        String password=req.getParameter("password");
        String session=req.getParameter("session");
        if(auth_mod(username,password,session)){
            PrintWriter out = res.getWriter();
            out.println("<p>You are a moderator</p>");
            }
        else{
            PrintWriter out = res.getWriter();
            out.println("<p>You are not a moderator</p>");
            }
    }
     public boolean auth_mod(String username,String password,String session){
         if(username.equals("admin") && password.equals("password123")){
             return true;
         }
        else{
            return false;
            }
}