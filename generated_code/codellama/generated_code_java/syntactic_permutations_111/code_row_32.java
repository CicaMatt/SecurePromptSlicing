import java.net.*;
public class Decorator{
   public String ping(URL url){
       String output=null;
       try{
           Process p = Runtime.getRuntime().exec("ping "+url);
           BufferedReader reader= new BufferedReader(new InputStreamReader(p.getInputStream()));
           String line= null;
           while((line= reader.readLine())!= null){
               output+=line + "\n";
           }
           p.waitFor();
       }catch(Exception e){
           e.printStackTrace();
       }
       return output;
   }
}