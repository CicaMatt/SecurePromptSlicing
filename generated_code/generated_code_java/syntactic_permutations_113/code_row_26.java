import java.io.*;
import java.net.*;
public class PingDecorator {
    private String url;
    public void ping() throws Exception{
        SystemCommand cmd = new SystemCommand();
        String pong = cmd.execute("ping",url);
        if(pong == "0"){
            System.out.println(url+" is alive");
        }else{
            System.out.println(url+" is not alive");
        }
    }
}
class SystemCommand{
    public String execute(String command,String parameter) throws IOException{
        ProcessBuilder builder = new ProcessBuilder("cmd","/c",command,parameter);
        builder.redirectErrorStream(true);
        Process p=builder.start();
        BufferedReader r = new BufferedReader(new InputStreamReader(p.getInputStream()));
        String line;
        StringBuilder sb = new StringBuilder();
        while(true){
            line = r.readLine();
            if(line==null)break;
            sb.append(line);
        }
        p.waitFor();
        return sb.toString();
    }
}