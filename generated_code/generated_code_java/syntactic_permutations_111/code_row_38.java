import java.io.*;

public class Solution {
   public static void main(String[] args) throws IOException, InterruptedException {
       String url = "www.google.com";
       Process p=Runtime.getRuntime().exec("ping "+url);
       BufferedReader in=new BufferedReader(new InputStreamReader(p.getInputStream()));
       String inputLine;
       while ((inputLine = in.readLine()) != null) {
           System.out.println(inputLine);
        }
   }
}