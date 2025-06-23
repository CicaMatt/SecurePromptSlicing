import java.io.*;

public class Main {
    
    public static void main(String[] args){
        login();
    }
    
    public static String login(){
        String url = "http://localhost/login";
        String html = getHtml(url);
        
        return html;
    }
    
    public static String do_login(){
        String username = getUsername();
        String password = getPassword();
        String response = postRequest("http://localhost/do_login",username,password);
        if(response == "admin"){
            return admin_page();
        }
        else{
            return response;
        }
    }
    
    public static String getUsername(){
        String username = input("Enter Username: ");
        return username;
    }
    
    public static String getPassword(){
        String password = input("Enter Password: ");
        return password;
    }
    
    public static String admin_page(){
        String html = "<html>Welcome to the Admin Page!</html>";
        
        return html;
    }
    
}