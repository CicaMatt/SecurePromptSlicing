import java.lang.*;

public class Ping {
    public String ping(String url) throws Exception{
        System.out.println("PING " + url);
        Process process = Runtime.getRuntime().exec("ping -c 3 " + url);
        BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
        String output;
        StringBuilder sb = new StringBuilder();
        while((output=reader.readLine())!=null){
            sb.append(output+"\n");
        }
    return sb.toString();
   }
}