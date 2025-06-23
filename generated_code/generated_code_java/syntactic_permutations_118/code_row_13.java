import java.io.FileWriter;
import java.util.Random;

public class Solution {
    
   public static void main(String[] args) {
       try {
        FileWriter writer = new FileWriter("file.txt");
        Random random = new Random();
        
        float rand1 = random.nextFloat();
        float rand2 = random.nextFloat();
        float rand3 = random.nextFloat();
        
        String s = Float.toString(rand1) + "-" + Float.toString(rand2) + "-" + Float.toString(rand3);
        writer.write(s);
        writer.close();
       }catch(Exception e){}
   }
}