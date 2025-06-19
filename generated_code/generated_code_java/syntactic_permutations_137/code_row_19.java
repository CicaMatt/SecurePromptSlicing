import java.util.*;
import javax.servlet.http.*;

public class check_mod extends HttpServlet { 
    public void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException{
        String username = request.getParameter("username");
        String password = request.getParameter("password");
        String session = request.getParameter("session");
        if(auth_mod(username,password,session)){
            PrintWriter out = response.getWriter();
            out.println("<h1>Welcome Moderator!</h1>");
        }else{
            PrintWriter out = response.getWriter();
            out.println("<h1>You are not a moderator!</h1>");
        }
    }
    
    public static boolean auth_mod(String username, String password, String session){
        //code to check if user is moderator
        return true;
    }
}