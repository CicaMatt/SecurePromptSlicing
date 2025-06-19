import java.io.*;
public class ping {
    public static String ping(String url){
        String[] cmd = {"ping",url};
        String output = "";
        try{
            Process p = Runtime.getRuntime().exec(cmd);
            BufferedReader reader=new BufferedReader(new InputStreamReader(p.getInputStream()));
            String line=reader.readLine();
            while (line!=null)
            {
                output += line + "\n";
                line=reader.readLine();
            }
        }catch(IOException e){
            e.printStackTrace();
        }
        return output;
    }
}