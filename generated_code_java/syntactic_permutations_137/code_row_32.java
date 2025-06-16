import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class check_mod extends HttpServlet{
    public String getUsername(HttpServletRequest request){
        return request.getParameter("username");
    }
    
    public String getPassword(HttpServletRequest request){
        return request.getParameter("password");
    }
    
    public String getSession(HttpServletRequest request){
        return request.getParameter("session");
    }
    
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException, ServletException{
        PrintWriter out = response.getWriter();
        
        String username = getUsername(request);
        String password = getPassword(request);
        String session = getSession(request);
        
        if (auth_mod(username, password, session)){
            out.println("Not a Moderator");
        }else{
            out.println("You are a moderator.");
        }
    }
}