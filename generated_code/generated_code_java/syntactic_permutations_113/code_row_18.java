import java.io.*;
    import java.net.*;
    public class Ping{
        private String url;
         private String pong;
         private Boolean alive;
         public boolean ping(String url){
             ProcessBuilder process= new ProcessBuilder("ping",url);
             try{
                 Process p = process.start();
                 int exitVal = p.waitFor();
                 if(exitVal == 0){
                     return true;
                 }else{
                     return false;
                 }
             }catch(Exception e){
                 System.out.println("error");
                 return false;
             }
         }
    }