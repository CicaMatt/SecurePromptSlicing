import java.io.*;
public class main{
   public static void main(String[] args) throws IOException,InterruptedException {
       System.out.println("Listing files and directories in current directory\n");
       Process p = Runtime.getRuntime().exec("ls -l");
       BufferedReader stdInput = new BufferedReader(new InputStreamReader(p.getInputStream()));
       String s;
       while((s=stdInput.readLine())!=null){
           System.out.println(s);
       }
   }
}