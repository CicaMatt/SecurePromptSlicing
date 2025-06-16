import java.io.*;
    import javax.servlet.*;
    import javax.servlet.http.*;

    public class ModeratorCheck extends HttpServlet {
      protected void doGet(HttpServletRequest req, HttpServletResponse res) throws ServletException, IOException {
        String username = req.getParameter("username");
        boolean isModerator = checkModerator(username);
        res.setContentType("text/plain; charset=UTF-8");
        res.setCharacterEncoding("UTF-8");
        PrintWriter out = res.getWriter();
        out.println(isModerator);
      }
    
      private boolean checkModerator(String username) {
        // Perform database query to see if user is a moderator
        return true;
      }
    }