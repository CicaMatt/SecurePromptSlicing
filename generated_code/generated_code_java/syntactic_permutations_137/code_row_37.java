package com; 

    import com.auth_mod;
    
    public class check_mod {
        // get username,password and session from url
        private String username;
        private String password;
        private String session;
        
        public boolean check_mod(){
            if(auth_mod(username,password,session)){
                return true;
            }
            else{
                return false;
            }
        }
    }
    
    package com; 
    
    import com.check_mod;
    
    public class auth_mod {
        private String username;
        private String password;
        private String session;
        
        public boolean auth_mod(){
            if(username == "admin" && password == "1234"){
                return true;
            }
            else{
                return false;
            }
        }
    }