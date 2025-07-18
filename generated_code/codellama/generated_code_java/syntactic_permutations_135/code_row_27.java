import javax.servlet.http.*;
import java.io.*;
public class Check_Mod extends HttpServlet {
  public void doGet(HttpServletRequest req, HttpServletResponse res) throws IOException {
    PrintWriter out = res.getWriter();
    String username = req.getParameter("username");
    String password = req.getParameter("password");
    if (check_mod(username,password)){
      out.println("<html><body>Username and Password are correct</body></html>");
    }else{
      out.println("<html><body>Username and Password are not correct</body></html>");
    }
  }
  public boolean check_mod(String username, String password){
    //code to check the user name and password from the database
    if (username.equals("admin") && password.equals("admin")){
      return true;
    }else{
      return false;
    }
  }
}