import java.io.*;

public class http_hello_page {
    public static void main(String[] args) throws Exception{
        FileInputStream request = new FileInputStream("request");
        FileOutputStream response = new FileOutputStream("response"); 
        int c=0;
        String username="";
        while((c=request.read()) != -1){
            if(Character.isLetterOrDigit(c)){
                username += (char)c;
            }
        }
        response.write("Hello ".getBytes());
        response.write(username.getBytes());
    }
}