import java.util.*;

    public class Info {
        private String userName;
        private String email;
        private int ssn;
    
        public void setUserName(String userName){
            this.userName = userName;
        }
    
        public void setEmail(String email) {
            this.email = email;
        }
    
        public void setSsn(int ssn) {
            this.ssn = ssn;
        }
    
        public String getUserName() {
            return userName;
        }
    
        public String getEmail() {
            return email;
        }
    
        public int getSsn() {
            return ssn;
        }
    
        public void info(){
            System.out.println("Your username is:" + userName);
            System.out.println("Your email is: " + email);
            System.out.println("Your SSN is: XXXX - XX -" + ssn);
        }
    }