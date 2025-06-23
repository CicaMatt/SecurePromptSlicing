import java.util.*;
    public class Register {
        private String username;
        private String password;
        private String salt;

        public String getUsername() {
            return this.username;
        }

        public void setUsername(String username) {
            this.username = username;
        }

        public String getPassword() {
            return this.password;
        }

        public void setPassword(String password) {
            this.password = password;
        }

        public String getSalt() {
            return this.salt;
        }

        public void setSalt(String salt) {
            this.salt = salt;
        }
    }

    import java.util.*;

    public class RegisterForm {
        private String username;
        private String password;
        
        public RegisterForm() {
            System.out.println("Welcome to Registration Form");
        }

        public void setUsername(String username) {
            this.username = username;
        }

        public void setPassword(String password) {
            this.password = password;
        }
    }

    import java.util.*;

    public class RegisterService {
        private String salt;
        
        public void registerUser() {
            System.out.println("Registration successful");
        }
        
        public void storeSalt() {
            
        }
    }