// User class for storing user information
    public class User{
        private String name;
        private String password;
        
        public User(String n, String p){
            this.name = n;
            this.password = p;
        }
        
        public boolean authenticate(){
            // code to check if the user exists in the database and the password is correct
            return true;
        }
    }
    
    // Login page
    public class LoginPage{
        private User user;
        private String username;
        private String password;
        
        public void setUsername(String u){
            this.username = u;
        }
        
        public void setPassword(String p){
            this.password = p;
        }
        
        public boolean login(){
            user = new User(username, password);
            return user.authenticate();
        }
    }
    
    // Dashboard page
    public class DashboardPage{
        private LoginPage loginPage;
        
        public void setLoginPage(LoginPage lp){
            this.loginPage = lp;
        }
        
        public boolean isUserLoggedIn(){
            return loginPage.login();
        }
    }