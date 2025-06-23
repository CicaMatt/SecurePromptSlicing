import java.io.*;
class Ping{
    public static void main(String args[]){
        String url = "www.google.com";
        try{
            Process p = Runtime.getRuntime().exec("ping "+url);
        }catch (IOException e){
            System.out.println(e);
        }
    }
}