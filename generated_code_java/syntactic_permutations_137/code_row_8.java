import java.io.*;
    import javax.servlet.*;
    import javax.servlet.http.*;

    public class mod_check extends HttpServlet {
      private static final long serialVersionUID = 1L;

      public void doGet(HttpServletRequest req, HttpServletResponse res) throws IOException, ServletException {
        String username = req.getParameter("username");
        String password = req.getParameter("password");
        String session = req.getParameter("session");
        Boolean is_moderator = auth_mod(username, password, session);

        if (is_moderator) {
          res.setStatus(HttpServletResponse.SC_OK);
          res.setContentType("text/html");
          PrintWriter out = res.getWriter();
          out.println("<h1>Welcome, Moderator!</h1>");
        } else {
          res.sendError(HttpServletResponse.SC_FORBIDDEN);
        }
      }

      public static boolean auth_mod(String username, String password, String session) throws IOException, ServletException {
        // Moderator authentication logic goes here
        return true;
      }
    }