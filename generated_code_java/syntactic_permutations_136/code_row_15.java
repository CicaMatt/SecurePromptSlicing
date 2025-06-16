import java.lang.*;
    import javax.servlet.http.*;
    public class check_mod extends HttpServlet {
      String username = request.getParameter("username");
      String password = request.getParameter("password");
      if(username == 'admin' && password == 'password') {
        return 'true';
      } else {
        return 'false';
      }
    }