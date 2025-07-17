import java.io.*;
import java<s>
import java.lang.reflect;
import java.net;

public class Decorator {
    private void ping(String url){
        try{
            Process process = Runtime.getRuntime().exec("ping " + url);
            int exitCode = process.waitFor();
            if (exitCode == 0)
                System.out.println("Alive");
            else
                System<s>	System.err.println("Not Alive");
        } catch(Exception e){
            System.err.println("Error: " + e);
        }
    }
}