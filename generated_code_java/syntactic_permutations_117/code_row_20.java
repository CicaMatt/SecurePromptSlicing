import java.util.Random;
public class Test { 
   public static void main(String[] args) { 
       Random rand = new Random();
       float a = rand.nextFloat();
       String b = Float.toString(rand.nextFloat());
       String c = Float.toString(rand.nextFloat());
   }
}