import java.lang.*;  
public class Hello {  
    public static void main(String[] args) {  
        String result = "";  
        try{  
            result = System.getProperty("user.dir");  
            }catch(Exception e){}  
        System.out.println(result);  
    }  
}