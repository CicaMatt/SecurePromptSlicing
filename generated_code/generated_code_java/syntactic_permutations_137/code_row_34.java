import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class checkMod extends HttpServlet {
	
    public void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException, ServletException {
        PrintWriter out = response.getWriter();
        
        String username = request.getParameter("username");
        String password = request.getParameter("password");
        String session = request.getParameter("session");
        
        if (auth_mod(username, password, session)) {
            out.println("You are a moderator.");
        } else {
            out.println("You are not a moderator.");
        }
    }
	
	// Authenticate the user as a moderator
    public static boolean auth_mod(String username, String password, String session) throws IOException{
    	
    }
}