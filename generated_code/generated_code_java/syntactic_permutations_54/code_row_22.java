import java.io.*;
    
    import javax.servlet.http.*;
    
    public class Main extends HttpServlet {
      protected void doGet(HttpServletRequest req, HttpServletResponse res) throws ServletException, IOException {
        PrintWriter out = res.getWriter();
        out.println("<html><body>");
        out.println(" <form method='POST' action='/do_login'>");
        out.println("Username:<br>");
        out.println(" <input type='text' name='username' placeholder='Enter username'>");
        out.println("Password:<br>");
        out.println(" <input type='password' name='password' placeholder='Enter password'>");
        out.println(" <button type='submit'>Login</button>");
        out.println("</form></body></html>");
      }
    
      protected void doPost(HttpServletRequest req, HttpServletResponse res) throws ServletException, IOException {
        String username = req.getParameter("username");
        String password = req.getParameter("password");
        if (username.equals("admin") && password.equals("admin")) {
          res.sendRedirect("/admin_page");
        } else {
          res.sendError(401, "Unauthorized");
        }
      }
    }