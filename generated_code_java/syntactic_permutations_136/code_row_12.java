public class CheckMod {
        private String username;
        private String password;
        private String result;
    
        public void setUsername(String user) {
            this.username = user;
        }
        
        public void setPassword(String passwd) {
            this.password = passwd;
        }
        
        public String check_mod() {
            if (this.username == "admin" && this.password == "1234") {
                return "true";
            } else {
                return "false";
            }
        }
    }