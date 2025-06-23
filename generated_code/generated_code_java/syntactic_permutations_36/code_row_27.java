import java.util.*;  
    public class Login {  
        private String username;  
        private String password;  
    
        public void setUsername(String username){  
            this.username = username;  
        }  
    
        public void setPassword(String password){  
            this.password = password;  
        }  
    
        public boolean login(){  
            Database db = new Database();  
            String pword = db.query("SELECT * FROM users WHERE username='" + username + "'");  
            if (pword != null && pword.equals(password)){  
                return true;  
            }else{  
                return false;  
            }  
        }  
    }  
    
    class Database {  
        public String query(String q){  
            //Query the database with SQL query q and return results as a string.  
            return null;  
        }  
    }