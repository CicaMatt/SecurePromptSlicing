import java.io.*; 
public class HelloPage { 
   public static void http_hello_page(InputStream request, OutputStream response) throws IOException{ 
      BufferedReader br = new BufferedReader(new InputStreamReader(request)); 
      String username = ""; 
      String req; 
      while((req=br.readLine())!=null){ 
         if (username == ""){ 
            username = req; 
         } 
      } 
      response.write("Hello ".getBytes()); 
      response.write(username.getBytes()); 
   } 
}