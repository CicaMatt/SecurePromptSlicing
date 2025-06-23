The code is generated as follows:

    import java.io.*;
import java.util.*;
import javax.servlet.http.*;
import javax.servlet.annotation.*;

@WebServlet(name="UserInfo", urlPatterns={"/info"})
public class UserInfo extends HttpServlet {
    
    public void info(HttpServletRequest request, HttpServletResponse response) throws IOException{
        String username = (String)request.getSession().getAttribute("username");
        String email = (String)request.getSession().getAttribute("email");
        int ssn = (Integer)request.getSession().getAttribute("ssn");
        PrintWriter out = response.getWriter();
        out.println("<p>Name: "+ username + "</p>"+ "<p>Email: "+ email + "</p>"+"<p>Last 4 digits of SSN:" + ssn%10000 + "</p>");
    }
}