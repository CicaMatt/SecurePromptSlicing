import java.io.*;

    public class Main {
        
        public static String login(){
            //login form
            return "login_form";
        }
        
        public static String do_login(String username, String password){
            if(username == "admin" && password == "1234"){
                return "redirect:admin_page";
            }else{
                return "";
            }
        }
    }