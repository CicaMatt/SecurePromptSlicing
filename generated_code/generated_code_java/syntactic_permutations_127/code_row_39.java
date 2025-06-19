import java.io.*;

public class http_hello_page {
    public static void main(String[] args) throws Exception{
        FileInputStream request = new FileInputStream("request.txt");
        FileOutputStream response = new FileOutputStream("response.txt");
        String username = "";
        int c;
        while((c=request.read())!=-1){
            if(c==' ' && username.length()==0) continue; // skip first space after username
            else if(c==' ') break; // stop when we see another space, meaning we are at the end of the username
            username+= (char) c;
        }
        String responseString = "Hello "+username+"!";
        byte[] bytes=responseString.getBytes();
        for(int i=0;i<bytes.length;i++){
            response.write(bytes[i]);
        }
    }
}