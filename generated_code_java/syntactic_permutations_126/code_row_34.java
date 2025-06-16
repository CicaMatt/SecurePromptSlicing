import java.util.*;

public class http_hello_page{
    public String username = "";
    public String outputbuf = "";
    public void http_hello_page(){
        if(!username.equals("")){ 
            outputbuf += "<html><body>Hello " + username + "</body></html>";
        }
    }
}