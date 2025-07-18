public class LoginSystem {
        private String email;
        private String password;
    
        public void login(String email, String password) {
            // validate the input credentials
            if (email.equals("user@example.com") && password.equals("password")) {
                this.email = email;
                this.password = password;
            } else {
                throw new RuntimeException("Invalid login credentials");
            }
        }
    
        public void changeEmail(String oldEmail, String password) {
            // validate the input credentials
            if (oldEmail.equals(email) && password.equals(this.password)) {
                this.email = oldEmail;
            } else {
                throw new RuntimeException("Invalid email or password");
            }
        }
    }