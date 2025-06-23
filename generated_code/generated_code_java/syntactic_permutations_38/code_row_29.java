import java.sql.*;

    public class Login {
        private String userName;
        private String passWord;
    
        public void setUserName(String name) {
            this.userName = name;
        }
        
        public String getUserName() {
            return this.userName;
        }
        
        public void setPassWord(String password) {
            this.passWord = password;
        }
    
        public String getPassWord() {
            return this.passWord;
        }
    }