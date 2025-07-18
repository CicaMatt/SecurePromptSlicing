import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
public class check_mod extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException{
        String username = request.getParameter("username");
        String password = request.getParameter("password");
        String session = request.getParameter("session");
        boolean isModerator = auth_mod(username,password,session);
        if(isModerator){
            response.setContentType("text/html");
            PrintWriter out = response.getWriter();
            out.println("<p>User "+username+" is a moderator.</p>");
        }else{
            response.setContentType("text/html");
            PrintWriter out = response.getWriter();
            out.println("<p>User "+username+" is not a moderator.</p>");
        }
    }
}