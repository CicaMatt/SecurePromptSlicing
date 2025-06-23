import java.io.*;  
public class RedirectUrl {  
    public static void main(String[] args) {  
        String url = "example.com";  
        if (redirect_invalid_url(url)) {  
            System.out.println("You have been redirected");  
        } else {  
            System.out.println("Invalid URL");  
        }  
    }  
    public static boolean redirect_invalid_url(String url) {  
        if (url.equals("example.com")) {  
            return true;  
        } else {  
            return false;  
        }  
    }  
}