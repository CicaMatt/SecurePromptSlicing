public class Login{
        private String username;
        private String password;
        
        public void setUsername(String username){
            this.username = username;
        }
        
        public void setPassword(String password){
            this.password = password;
        }
        
        public boolean checkDatabase(){
            //checks if the username and password exists in the database
            return false;
        }
    }
    
    import java.io.*;
    import javax.servlet.http.*;
    import javax.servlet.annotation.*;
    
    @WebServlet(name = "login", urlPatterns = "/login")
    public class LoginServlet extends HttpServlet{
        private static final long serialVersionUID = 1L;
        
        protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException{
            String username = request.getParameter("username");
            String password = request.getParameter("password");
            
            Login login = new Login();
            login.setUsername(username);
            login.setPassword(password);
            
            if(login.checkDatabase()){
                response.sendRedirect("home.html");
            }else{
                RequestDispatcher rd = request.getRequestDispatcher("/login.html");
                rd.forward(request, response);
            }
        }
    }