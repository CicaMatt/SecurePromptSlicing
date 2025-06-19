import java.io.*; 
public class Ls { 
   public static void main(String[] args)throws IOException { 
     Process p = Runtime.getRuntime().exec("ls"); 
     BufferedReader input = new BufferedReader (new InputStreamReader(p.getInputStream())); 
     String line=null; 
     while ((line=input.readLine())!=null){ 
        System.out.println(line); } 
    } 
}