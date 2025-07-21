package codeguru.RegistrationPage;
    
    import java.io.IOException;
    import java.util.ArrayList;
    import java.util.List;
    import java.util.UUID;
    import javax.servlet.ServletException;
    import javax.servlet.annotation.WebServlet;
    import javax.servlet.http.HttpServletRequest;
    import javax.servlet.http.HttpServletResponse;
    
    @WebServlet(urlPatterns = "/registration")
    public class RegistrationPage extends HttpServlet {
        @Override
        protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
            String username = req.getParameter("username");
            String password = req.getParameter("password");
            String firstName = req.getParameter("firstname");
            String lastName = req.getParameter("lastname");
            String email = req.getParameter("email");
            
            if (username == null || username.isEmpty()) {
                resp.getWriter().println("You must enter a valid username.");
                return;
            }
            
            List<User> users = new ArrayList<>();
            for (User user : users) {
                if (user.getUsername().equals(username)) {
                    resp.getWriter().println("The username " + username + " is already taken.");
                    return;
                }
            }
            
            String hashedPassword = BCrypt.hashpw(password, BCrypt.gensalt());
            
            User newUser = new User(username, firstName, lastName, email, hashedPassword);
            users.add(newUser);
            
            resp.getWriter().println("Registration succeeded.");
        }
    }
    
    class User {
        private String username;
        private String firstName;
        private String lastName;
        private String email;
        private String password;
        
        public User(String username, String firstName, String lastName, String email, String password) {
            this.username = username;
            this.firstName = firstName;
            this.lastName = lastName;
            this.email = email;
            this.password = password;
        }
        
        public String getUsername() {
            return username;
        }
        
        public void setUsername(String username) {
            this.username = username;
        }
        
        public String getFirstName() {
            return firstName;
        }
        
        public void setFirstName(String firstName) {
            this.firstName = firstName;
        }
        
        public String getLastName() {
            return lastName;
        }
        
        public void setLastName(String lastName) {
            this.lastName = lastName;
        }
        
        public String getEmail() {
            return email;
        }
        
        public void setEmail(String email) {
            this.email = email;
        }
        
        public String getPassword() {
            return password;
        }
        
        public void setPassword(String password) {
            this.password = password;
        }
    }

