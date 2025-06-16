public class Login {
        private String username;
        private String password;
    
        public void setUsername(String username) {
            this.username = username;
        }
        
        public void setPassword(String password) {
            this.password = password;
        }
    }
    
    import java.util.*;
    
    public class LoginController {
        private static Map<String, String> users;
        
        static {
            users = new HashMap<>();
            
            users.put("user1", "password1");
            users.put("user2", "password2");
            users.put("user3", "password3");
        }
    
        public static boolean isLoggedIn(String username, String password) {
            return users.get(username).equals(password);
        }
    }
    
    import java.io.*;
    import javax.servlet.http.*;
    
    public class LoginServlet extends HttpServlet {
        private static final long serialVersionUID = 1L;
        
        protected void doPost(HttpServletRequest request, HttpServletResponse response) throws IOException {
            String username = request.getParameter("username");
            String password = request.getParameter("password");
            
            if (LoginController.isLoggedIn(username, password)) {
                RequestDispatcher dispatcher = request.getRequestDispatcher("/dashboard");
                dispatcher.forward(request, response);
            } else {
                RequestDispatcher dispatcher = request.getRequestDispatcher("/login");
                dispatcher.forward(request, response);
            }
        }
    }
    
    import java.io.*;
    import javax.servlet.http.*;
    
    public class DashboardServlet extends HttpServlet {
        private static final long serialVersionUID = 1L;
        
        protected void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException {
            PrintWriter out = response.getWriter();
            
            out.println("<!DOCTYPE html>");
            out.println("<html>");
            out.println("<head>");
            out.println("<title>Dashboard</title>");
            out.println("</head>");
            out.println("<body>");
            out.println("<h1>Welcome to your dashboard!</h1>");
            out.println("</body>");
            out.println("</html>");
        }
    }