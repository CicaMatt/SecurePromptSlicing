import java.util.regex.*;
import java.io.*;

public class Redirect{
    public static void main(String[] args){
        String query = "target=http://www.example.com/mypage.html";
        Pattern pattern = Pattern.compile("^[a-zA-Z0-9]+\\-*");
        Matcher matcher = pattern.matcher(query);
        
        if (matcher.find()){
            String target = query.substring(target.indexOf("=") + 1);
            System.out.println(target);
        }else{
            System.out.println("/");
        }
    }
}