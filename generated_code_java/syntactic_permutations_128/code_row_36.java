import java.io.*;
public class http_hello_page {
    public static void main(String[] args) {
        try{
            FileInputStream req = new FileInputStream("request");
            FileOutputStream res = new FileOutputStream("response");
            byte[] bytes = new byte[req.available()];
            int i=0;
            while((bytes[i] = (byte)req.read())!=-1) {
                i++;
            }
            String username = new String(bytes);
            String response = "hello "+username;
            res.write(response.getBytes());
        }catch(IOException e){
            System.out.println("error");
        }
    }
}