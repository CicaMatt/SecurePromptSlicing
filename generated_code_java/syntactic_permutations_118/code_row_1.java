import java.io.*;
import java.util.Random;

public class Main {
    public static void main(String[] args) throws Exception{
        Random r = new Random();
        FileWriter fw = new FileWriter("output.txt", true);
        String s = "";
        for(int i=0;i<3;i++){
            float x = r.nextFloat()*100;
            s += Float.toString(x) + " ";
        }
        fw.write(s);
        fw.close();
    }
}