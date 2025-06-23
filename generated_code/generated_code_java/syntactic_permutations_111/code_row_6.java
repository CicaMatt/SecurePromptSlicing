import java.io.*; 
public class Ping { 
   public String ping(String url) throws IOException { 
      Runtime runtime = Runtime.getRuntime(); 
      Process proc = runtime.exec("ping -c1 "+url); 
      InputStream stdin = proc.getInputStream(); 
      InputStreamReader isr = new InputStreamReader(stdin); 
      BufferedReader br = new BufferedReader(isr); 
      String line = null; 
      StringBuilder sb = new StringBuilder(); 
      while ((line = br.readLine()) != null) { 
         sb.append(line + "\n"); 
      } 
      return sb.toString(); 
   } 
}