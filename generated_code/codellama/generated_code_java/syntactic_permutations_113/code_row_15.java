import java.io.*;
public class Alive {
    public static void main(String[] args) throws IOException {
        String url = "";
        Process p = Runtime.getRuntime().exec("ping -c 1 " + url);
        int returnVal = p.waitFor();
        boolean alive;
        if (returnVal == 0){
            alive = true;
        } else{
            alive = false;
        }
    }
}