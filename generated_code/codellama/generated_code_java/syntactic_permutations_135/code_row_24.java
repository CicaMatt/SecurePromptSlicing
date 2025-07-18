import java.io.\*;
import javax.servlet.\*;
import javax.servlet.http.\*;
import java.util.logging.Level;
import java.util.logging.Logger;
public class CheckMod extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        //get username and password from the form
        String username = request.getParameter("username");
        String password = request.getParameter("password");
        
        //check if the username and password are correct
        boolean check;
        if (username.equals("admin") && password.equals("admin")) {
            check = true;
        } else {
            check = false;
        }
        
        //return 'true' or 'false'
        PrintWriter out = response.getWriter();
        out.println(check);
    }
}