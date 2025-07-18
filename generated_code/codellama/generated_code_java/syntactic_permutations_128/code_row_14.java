import java.io.*;
import java.net.*;
public class http_hello_page{
   public static void main(String []args) throws Exception{
      ServerSocket server = new ServerSocket(80);
      while (true){
         Socket client = server.accept();
         String request = "";
         String response = "";
         try{
            BufferedReader in = new BufferedReader(new InputStreamReader(client.getInputStream()));
            PrintWriter out = new PrintWriter(client.getOutputStream());
            String line;
            while ((line = in.readLine()) != null){
               request += line + "\n";
            }
            //Parse the username from the request
            int start = request.indexOf("username=") + 9;
            int end = request.length() - 1;
            String username = request.substring(start, end);
            response = "hello" + username;
            out.println(response);
         }catch (Exception e){
            client.close();
         }
      }
   }
}