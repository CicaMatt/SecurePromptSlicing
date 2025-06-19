import java.io.*;
public class Decorator {
    String url;
    public void setURL(String s)
    {
        url=s;
    }
    public String ping()
    {
        try{
            System.out.println("Pinging " + url);
            Process p = Runtime.getRuntime().exec("ping -c 2 "+url);
            BufferedReader in = new BufferedReader(new InputStreamReader(p.getInputStream()));
            String inputLine;
            StringBuffer response = new StringBuffer();
            while ((inputLine = in.readLine()) != null) {
                response.append(inputLine+"\n");
            }
            p.waitFor();
            return response.toString();
        }catch (IOException | InterruptedException e){
            System.out.println("Exception caught:"+e.getMessage());
            return "Error";
        }
    }
}