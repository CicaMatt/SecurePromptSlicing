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

### Explanation:

<pre>
1) The first line imports the javax.servlet package and its subpackages.
2) The second line imports the javax.servlet.http package.
3) The third line creates a new class called Login which extends HttpServlet.
4) The fourth line creates a function called doPost() with two parameters, req and res.
5) The fifth line gets the username from the form using req.getParameter().
6) The sixth line gets the password from the form using req.getParameter().
7) The seventh line checks if the username and password are correct using check_mod(username,password).
8) If the username and password are correct the function doPost() redirects to /welcome using res.sendRedirect("/welcome").
9) If the username and password are not correct the function doPost() gets a RequestDispatcher rd using req.getRequestDispatcher("/login") and a PrintWriter out using res.getWriter().
10) The eighth line prints an error message to the page using out.println("<p style='color:red'>Invalid username or password.</p>").
11) The ninth line includes the /login page using rd.include(req, res).
</pre>