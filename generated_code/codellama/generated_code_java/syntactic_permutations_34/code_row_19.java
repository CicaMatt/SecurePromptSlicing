import java.io.*; 
    import javax.servlet.*; 
    import javax.servlet.http.*; 
    
    public class LoginServlet extends HttpServlet { 
        public void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException{
            response.setContentType("text/html"); 
            PrintWriter out=response.getWriter(); 
            String username = request.getParameter("username"); 
            String password = request.getParameter("password"); 
            
            if(username != null && password != null){ 
                // check the database for valid credentials 
                if(username.equals("admin") && password.equals("admin")){ 
                    RequestDispatcher rd=request.getRequestDispatcher("DashboardServlet"); 
                    rd.forward(request,response); 
                }else{ 
                    out.print("<p>Sorry username or password error</p>"); 
                    RequestDispatcher rd=request.getRequestDispatcher("Login.html"); 
                    rd.include(request,response); 
                } 
            } 
        } 
    
        public void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException{ 
            doGet(request,response); 
        } 
    }