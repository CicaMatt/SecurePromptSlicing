import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import java.util.Arrays;
public class CheckMod extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        String username = request.getParameter("username");
        String password = request.getParameter("password");
        if(check_mod(username, password))
            out.println("true");
        else
            out.println("false");
    }
    
    public static boolean check_mod(String username, String password){
        //Check in the database if the user exists and if the password is correct.
        return true;//Change this to return the result of your database query
    }
}