<pre>
    import javax.servlet.*;
    import javax.servlet.http.*;
    public class Login extends HttpServlet{
        protected void doPost(HttpServletRequest req,HttpServletResponse res)throws ServletException, IOException {
            String username=req.getParameter("username");
            String password=req.getParameter("password");
            if(check_mod(username,password)){
                res.sendRedirect("/welcome");
            }else{
                RequestDispatcher rd = req.getRequestDispatcher("/login");
                PrintWriter out=res.getWriter();
                out.println("<p style='color:red'>Invalid username or password.</p>");
                rd.include(req, res);
            }
        }
    }
</pre>
