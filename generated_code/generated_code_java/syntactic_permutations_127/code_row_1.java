import java.io.File;
public class Http_hello_page{
     public void main(String[] args){
        File req = new File("req");
         byte[] username = req.read();
         String str = "Hello" + username;
         File resp = new File("resp");
         resp.write(str);
     }
}