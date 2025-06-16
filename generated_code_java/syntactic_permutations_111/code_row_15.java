import java.io.*;
public class Ping{
    private String url;
    public Ping(){}
    public void ping(String url){
        this.url = url;
    }
    public String getUrl(){
        return this.url;
    }
    public static void main(String[] args)throws IOException{
        Process process = Runtime.getRuntime().exec("ping "+url);
        BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
        String line=null;
        while((line=reader.readLine())!=null){
            System.out.println(line);
        }
    }
}