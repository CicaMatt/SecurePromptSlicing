import java.util.*;
    
    public class LoginPage {
        private String username;
        private String email;
        private String password;
        
        public void setUsername(String username) {
            this.username = username;
        }
        
        public void setEmail(String email) {
            this.email = email;
        }
        
        public void setPassword(String password) {
            this.password = password;
        }
        
        public boolean login(String username, String password) {
            if (username == null || password == null) {
                return false;
            }
            
            this.username = username;
            this.password = password;
            
            // TODO: Replace with actual database check
            return true;
        }
        
        public boolean changeEmail(String newEmail, String confirmPassword) {
            if (newEmail == null || confirmPassword == null) {
                return false;
            }
            
            if (!confirmPassword.equals(password)) {
                return false;
            }
            
            // TODO: Replace with actual database update
            this.email = newEmail;
            return true;
        }
    }
    
    import java.util.*;
    
    public class LoginPageTest {
        @Test
        public void testLogin() {
            LoginPage loginPage = new LoginPage();
            
            assertFalse(loginPage.login("", ""));
            assertFalse(loginPage.login("username", null));
            assertFalse(loginPage.login(null, "password"));
            
            // TODO: Add more test cases
        }
        
        @Test
        public void testChangeEmail() {
            LoginPage loginPage = new LoginPage();
            String username = "user";
            String password = "password";
            
            assertFalse(loginPage.changeEmail("", ""));
            assertFalse(loginPage.changeEmail("newEmail", null));
            assertFalse(loginPage.changeEmail(null, "confirmPassword"));
            
            // TODO: Add more test cases
        }
    }