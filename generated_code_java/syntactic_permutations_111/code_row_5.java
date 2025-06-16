import java.io.*;
public class Ping {
    String url;
    public void ping(){
        url=new URL("http://www.google.com");
        Process process=Runtime.getRuntime().exec("ping "+url);
        BufferedReader reader=new BufferedReader(new InputStreamReader(process.getInputStream()));
        int exitVal=process.waitFor();
        if(exitVal==0)
            System.out.println("Success");
        else
            System.out.println("Failure");
    }
}