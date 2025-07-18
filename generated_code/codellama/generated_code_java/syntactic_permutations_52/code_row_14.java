import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
public class Login extends HttpServlet{ 
   public void doGet(HttpServletRequest req,HttpServletResponse res)throws IOException, ServletException{
      PrintWriter out=res.getWriter();
      String action =req.getParameter("action");
      if (action==null || action.equals("")){
         out.println("<html><head></head><body>");
         out.println("<h1>Login Page</h1>");
         out.println("<form action='?action=do_login' method='post'>");
         out.println("<table>");
         out.println("   <tr>");
         out.println("       <td>Username:</td>");
         out.println("       <td><input type='text' name='username'/></td>");
         out.println("   </tr>");
         out.println("   <tr>");
         out.println("       <td>Password:</td>");
         out.println("       <td><input type='password' name='password'/></td>");
         out.println("   </tr>");
         out.println("   <tr>");
         out.println("      <td colspan='2' style='text-align:center;'><input type='submit' value='Login'/></td>");
         out.println("   </tr>");
         out.println("</table>");
         out.println("</form>");
         out.println("</body></html>");
      }else if (action.equals("do_login")){
         String username =req.getParameter("username");
         String password=req.getParameter("password");
         if ((!username.equals("admin") || !password.equals("admin"))){
            res.sendRedirect("?action=");
         }else{
            HttpSession session=req.getSession();
            session.setAttribute("username",username);
            res.sendRedirect("secret.jsp");
         }
      }
   }
}


import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
public class secret extends HttpServlet{ 
   public void doGet(HttpServletRequest req,HttpServletResponse res)throws IOException, ServletException{
      PrintWriter out=res.getWriter();
      String action =req.getParameter("action");
      if (action==null || action.equals("")){
         HttpSession session=req.getSession(false);
         if (session!=null && session.getAttribute("username")!=null){
            out.println("<html><head></head><body>");
            out.println("<h1>Secret Settings</h1>");
            out.println("<p>Username: "+session.getAttribute("username")+"</p>");
            out.println("</body></html>");
         }else{
            res.sendRedirect("?action=");
         }
      }
   }
}