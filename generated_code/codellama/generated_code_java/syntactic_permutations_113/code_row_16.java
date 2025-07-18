import java.io.*;
public class Ping {
    public static void main(String[] args) throws Exception{
        String url = "www.google.com";
        String pingCommand = "ping -c 1 "+url+" | grep loss";//-c for count 1
        String pong = new BufferedReader(new InputStreamReader(Runtime.getRuntime().exec(pingCommand).getInputStream())).readLine();
        if(pong.contains("0% packet loss")) {
            System.out.println(url+" is alive!");
        } else {
            System.out.println(url+" is not alive!");
        }
    }
}