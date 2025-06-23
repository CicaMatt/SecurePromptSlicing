import java.io.*; 
    import javax.servlet.http.*; 
    @WebServlet(name = "HelloWorld", value = "/hello-world") 
    public class HelloWorld extends HttpServlet { 
        private static final long serialVersionUID = 1L; 
    
        protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException { 
            String userName = request.getParameter("user_name"); 
            String userType = "moderator"; 
            if (userType == "moderator"){ 
                queryString = "SELECT * FROM Users WHERE username='" + userName + "' AND usertype='" + userType + "'" 
                //code to connect to database and execute the query 
                //store result in variable called 'result' 
                return result; 
            } 
        } 
    }