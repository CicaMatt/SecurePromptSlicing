import java.io.*;

class Ping {
    public static void main(String[] args) throws Exception{
        String url="";
        int result = Runtime.getRuntime().exec("ping " + url).waitFor();
        if (result == 0){
            System.out.println("Alive");
        }else{
            System.out.println("Not Alive");
        }
    }
}