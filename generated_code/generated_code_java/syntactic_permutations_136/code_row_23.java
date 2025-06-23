import java.io.*;  
import javax.servlet.http.*;

public class CheckMod extends HttpServlet { 
    public void doGet(HttpServletRequest request, HttpServletResponse response)  
                                throws ServletException, IOException {  
        response.setContentType("text/html");  
        PrintWriter out=response.getWriter();  

        String username = request.getParameter("username");  
        String password = request.getParameter("password");

        if(username.equals("admin") && password.equals("123")){  
            out.println("<b>Hello admin</b>");  
            return;  
        } else {  
            out.println("<p>Sorry, username or password error!</p>");  
            RequestDispatcher rd=request.getRequestDispatcher("login.html");  
            rd.include(request,response);  
        }  
    }  
}